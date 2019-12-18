#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_15__ ;

/* Type definitions */
struct TYPE_28__ {int /*<<< orphan*/  lease_time; int /*<<< orphan*/  FsAttrs; int /*<<< orphan*/  path; scalar_t__ rsize; scalar_t__ wsize; int /*<<< orphan*/  sec_flavor; int /*<<< orphan*/  hostname; } ;
struct TYPE_21__ {TYPE_8__ mount; } ;
struct TYPE_23__ {TYPE_4__* root_ref; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; TYPE_1__ args; } ;
typedef  TYPE_3__ nfs41_upcall ;
struct TYPE_24__ {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
typedef  TYPE_4__ nfs41_root ;
struct TYPE_22__ {int /*<<< orphan*/  superblock; } ;
struct TYPE_25__ {TYPE_2__ fh; } ;
typedef  TYPE_5__ nfs41_path_fh ;
struct TYPE_26__ {TYPE_15__* session; } ;
typedef  TYPE_6__ nfs41_client ;
struct TYPE_27__ {unsigned short len; int /*<<< orphan*/  path; int /*<<< orphan*/  lock; } ;
typedef  TYPE_7__ nfs41_abs_path ;
typedef  int /*<<< orphan*/  multi_addr4 ;
typedef  TYPE_8__ mount_upcall_args ;
struct TYPE_20__ {int /*<<< orphan*/  lease_time; } ;

/* Variables and functions */
 int ERROR_BAD_NETPATH ; 
 int ERROR_FILENAME_EXCED_RANGE ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 TYPE_4__* INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  InitializeSRWLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS41_MAX_PATH_LEN ; 
 scalar_t__ READ_OVERHEAD ; 
 int /*<<< orphan*/  StringCchCopyA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WRITE_OVERHEAD ; 
 int /*<<< orphan*/  eprintf (char*,int,...) ; 
 int nfs41_lookup (TYPE_4__*,TYPE_15__*,TYPE_7__*,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nfs41_root_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,TYPE_4__**) ; 
 int /*<<< orphan*/  nfs41_root_deref (TYPE_4__*) ; 
 int nfs41_root_mount_addrs (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__**) ; 
 int /*<<< orphan*/  nfs41_root_ref (TYPE_4__*) ; 
 int nfs41_server_resolve (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs41_superblock_fs_attributes (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_mount(nfs41_upcall *upcall)
{
    int status;
    mount_upcall_args *args = &upcall->args.mount;
    nfs41_abs_path path;
    multi_addr4 addrs;
    nfs41_root *root;
    nfs41_client *client;
    nfs41_path_fh file;

    // resolve hostname,port
    status = nfs41_server_resolve(args->hostname, 2049, &addrs);
    if (status) {
        eprintf("nfs41_server_resolve() failed with %d\n", status);
        goto out;
    }

    if (upcall->root_ref != INVALID_HANDLE_VALUE) {
        /* use an existing root from a previous mount, but don't take an
         * extra reference; we'll only get one UNMOUNT upcall for each root */
        root = upcall->root_ref;
    } else {
        // create root
        status = nfs41_root_create(args->hostname, args->sec_flavor,
            args->wsize + WRITE_OVERHEAD, args->rsize + READ_OVERHEAD, &root);
        if (status) {
            eprintf("nfs41_root_create() failed %d\n", status);
            goto out;
        }
        root->uid = upcall->uid;
        root->gid = upcall->gid;
    }

    // find or create the client/session
    status = nfs41_root_mount_addrs(root, &addrs, 0, 0, &client);
    if (status) {
        eprintf("nfs41_root_mount_addrs() failed with %d\n", status);
        goto out_err;
    }

    // make a copy of the path for nfs41_lookup()
    InitializeSRWLock(&path.lock);
    if (FAILED(StringCchCopyA(path.path, NFS41_MAX_PATH_LEN, args->path))) {
        status = ERROR_FILENAME_EXCED_RANGE;
        goto out_err;
    }
    path.len = (unsigned short)strlen(path.path);

    // look up the mount path, and fail if it doesn't exist
    status = nfs41_lookup(root, client->session,
        &path, NULL, &file, NULL, NULL);
    if (status) {
        eprintf("nfs41_lookup('%s') failed with %d\n", path.path, status);
        status = ERROR_BAD_NETPATH;
        goto out_err;
    }

    nfs41_superblock_fs_attributes(file.fh.superblock, &args->FsAttrs);

    if (upcall->root_ref == INVALID_HANDLE_VALUE)
        nfs41_root_ref(root);
    upcall->root_ref = root;
    args->lease_time = client->session->lease_time;
out:
    return status;

out_err:
    if (upcall->root_ref == INVALID_HANDLE_VALUE)
        nfs41_root_deref(root);
    goto out;
}