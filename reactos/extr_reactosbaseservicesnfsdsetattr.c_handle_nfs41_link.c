#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_28__ {int /*<<< orphan*/  ctime; int /*<<< orphan*/  root; int /*<<< orphan*/  buf; TYPE_5__* state; } ;
typedef  TYPE_3__ setattr_upcall_args ;
typedef  int /*<<< orphan*/  nfs41_session ;
struct TYPE_27__ {scalar_t__ superblock; int /*<<< orphan*/  fileid; } ;
struct TYPE_32__ {scalar_t__ name; } ;
struct TYPE_29__ {TYPE_2__ fh; TYPE_7__ name; TYPE_1__* path; } ;
typedef  TYPE_4__ nfs41_path_fh ;
struct TYPE_30__ {TYPE_4__ file; int /*<<< orphan*/ * session; } ;
typedef  TYPE_5__ nfs41_open_state ;
struct TYPE_31__ {int /*<<< orphan*/  change; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_6__ nfs41_file_info ;
typedef  TYPE_7__ nfs41_component ;
struct TYPE_33__ {unsigned short len; scalar_t__ path; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_8__ nfs41_abs_path ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_34__ {int FileNameLength; int /*<<< orphan*/  ReplaceIfExists; int /*<<< orphan*/  FileName; } ;
struct TYPE_26__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_9__* PFILE_LINK_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int ERROR_FILE_EXISTS ; 
 int ERROR_FILE_NOT_FOUND ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_NOT_SAME_DEVICE ; 
 int ERROR_REPARSE ; 
 int ERROR_TOO_MANY_LINKS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NFS41_MAX_PATH_LEN ; 
 scalar_t__ NFS41_MAX_SYMLINK_DEPTH ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  OPEN_DELEGATE_READ ; 
 int /*<<< orphan*/  OPEN_DELEGATE_WRITE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintf (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  eprintf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  last_component (scalar_t__,scalar_t__,TYPE_7__*) ; 
 int /*<<< orphan*/  nfs41_delegation_return (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs41_link (int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*,TYPE_7__*,TYPE_6__*) ; 
 int nfs41_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_8__*,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int nfs41_remove (int /*<<< orphan*/ *,TYPE_4__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs41_root_session (int /*<<< orphan*/ ) ; 
 int nfs41_symlink_target (int /*<<< orphan*/ *,TYPE_4__*,TYPE_8__*) ; 
 int /*<<< orphan*/  nfs_error_string (int) ; 
 int nfs_to_windows_error (int,int) ; 
 int /*<<< orphan*/  path_fh_init (TYPE_4__*,TYPE_8__*) ; 

__attribute__((used)) static int handle_nfs41_link(setattr_upcall_args *args)
{
    nfs41_open_state *state = args->state;
    PFILE_LINK_INFORMATION link = (PFILE_LINK_INFORMATION)args->buf;
    nfs41_session *dst_session;
    nfs41_abs_path dst_path = { 0 };
    nfs41_path_fh dst_dir, dst;
    nfs41_component dst_name;
    uint32_t depth = 0;
    nfs41_file_info info = { 0 };
    int status;

    dst_path.len = (unsigned short)WideCharToMultiByte(CP_UTF8, 0,
        link->FileName, link->FileNameLength/sizeof(WCHAR),
        dst_path.path, NFS41_MAX_PATH_LEN, NULL, NULL);
    if (dst_path.len == 0) {
        eprintf("WideCharToMultiByte failed to convert destination "
            "filename %S.\n", link->FileName);
        status = ERROR_INVALID_PARAMETER;
        goto out;
    }
    path_fh_init(&dst_dir, &dst_path);

    /* the destination path is absolute, so start from the root session */
    status = nfs41_lookup(args->root, nfs41_root_session(args->root),
        &dst_path, &dst_dir, &dst, NULL, &dst_session);

    while (status == ERROR_REPARSE) {
        if (++depth > NFS41_MAX_SYMLINK_DEPTH) {
            status = ERROR_TOO_MANY_LINKS;
            goto out;
        }

        /* replace the path with the symlink target's */
        status = nfs41_symlink_target(dst_session, &dst_dir, &dst_path);
        if (status) {
            eprintf("nfs41_symlink_target() for %s failed with %d\n", 
                dst_dir.path->path, status);
            goto out;
        }

        /* redo the lookup until it doesn't return REPARSE */
        status = nfs41_lookup(args->root, dst_session,
            &dst_path, &dst_dir, &dst, NULL, &dst_session);
    }

    /* get the components after lookup in case a referral changed its path */
    last_component(dst_path.path, dst_path.path + dst_path.len, &dst_name);
    last_component(dst_path.path, dst_name.name, &dst_dir.name);

    if (status == NO_ERROR) {
        if (!link->ReplaceIfExists) {
            status = ERROR_FILE_EXISTS;
            goto out;
        }
    } else if (status != ERROR_FILE_NOT_FOUND) {
        dprintf(1, "nfs41_lookup('%s') failed to find destination "
            "directory with %d\n", dst_path.path, status);
        goto out;
    }

    /* http://tools.ietf.org/html/rfc5661#section-18.9.3
     * "The existing file and the target directory must reside within
     * the same file system on the server." */
    if (state->file.fh.superblock != dst_dir.fh.superblock) {
        status = ERROR_NOT_SAME_DEVICE;
        goto out;
    }

    if (status == NO_ERROR) {
        /* break any delegations and truncate the destination file */
        nfs41_delegation_return(dst_session, &dst,
            OPEN_DELEGATE_WRITE, TRUE);

        /* LINK will return NFS4ERR_EXIST if the target file exists,
         * so we have to remove it ourselves */
        status = nfs41_remove(state->session,
            &dst_dir, &dst_name, dst.fh.fileid);
        if (status) {
            dprintf(1, "nfs41_remove() failed with error %s.\n",
                nfs_error_string(status));
            status = ERROR_FILE_EXISTS;
            goto out;
        }
    }

    /* break read delegations on the source file */
    nfs41_delegation_return(state->session, &state->file,
        OPEN_DELEGATE_READ, FALSE);

    status = nfs41_link(state->session, &state->file, &dst_dir, &dst_name, 
            &info);
    if (status) {
        dprintf(1, "nfs41_link() failed with error %s.\n",
            nfs_error_string(status));
        status = nfs_to_windows_error(status, ERROR_INVALID_PARAMETER);
    }
    args->ctime = info.change;
out:
    return status;
}