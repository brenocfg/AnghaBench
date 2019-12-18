#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_31__ ;
typedef  struct TYPE_36__   TYPE_2__ ;
typedef  struct TYPE_35__   TYPE_26__ ;
typedef  struct TYPE_34__   TYPE_25__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_14__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_36__ {int /*<<< orphan*/  root; int /*<<< orphan*/  buf; TYPE_4__* state; } ;
typedef  TYPE_2__ setattr_upcall_args ;
typedef  int /*<<< orphan*/  nfs41_session ;
struct TYPE_34__ {scalar_t__ superblock; } ;
struct TYPE_40__ {scalar_t__ name; } ;
struct TYPE_38__ {TYPE_25__ fh; TYPE_5__ name; TYPE_1__* path; } ;
typedef  TYPE_3__ nfs41_path_fh ;
struct TYPE_35__ {scalar_t__ superblock; } ;
struct TYPE_32__ {TYPE_26__ fh; } ;
struct TYPE_37__ {int /*<<< orphan*/  lock; } ;
struct TYPE_39__ {TYPE_14__ parent; int /*<<< orphan*/ * session; TYPE_3__ file; TYPE_31__ path; } ;
typedef  TYPE_4__ nfs41_open_state ;
typedef  TYPE_5__ nfs41_component ;
struct TYPE_41__ {unsigned short len; scalar_t__ path; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_6__ nfs41_abs_path ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_42__ {int FileNameLength; int /*<<< orphan*/  ReplaceIfExists; scalar_t__ FileName; } ;
struct TYPE_33__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_7__* PFILE_RENAME_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  AcquireSRWLockShared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  ERROR_ACCESS_DENIED ; 
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
 int /*<<< orphan*/  OPEN_DELEGATE_WRITE ; 
 int /*<<< orphan*/  ReleaseSRWLockShared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abs_path_copy (TYPE_6__*,TYPE_31__*) ; 
 int /*<<< orphan*/  create_silly_rename (TYPE_6__*,TYPE_25__*,TYPE_5__*) ; 
 int /*<<< orphan*/  dprintf (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  eprintf (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  fh_copy (TYPE_25__*,TYPE_26__*) ; 
 int is_dst_name_opened (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  last_component (scalar_t__,scalar_t__,TYPE_5__*) ; 
 int /*<<< orphan*/  nfs41_delegation_return (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs41_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_6__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int nfs41_rename (int /*<<< orphan*/ *,TYPE_14__*,TYPE_5__*,TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/ * nfs41_root_session (int /*<<< orphan*/ ) ; 
 int nfs41_symlink_target (int /*<<< orphan*/ *,TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  nfs_error_string (int) ; 
 int nfs_to_windows_error (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_state_rename (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  path_fh_init (TYPE_3__*,TYPE_6__*) ; 

__attribute__((used)) static int handle_nfs41_rename(setattr_upcall_args *args)
{
    nfs41_open_state *state = args->state;
    nfs41_session *dst_session;
    PFILE_RENAME_INFO rename = (PFILE_RENAME_INFO)args->buf;
    nfs41_abs_path dst_path = { 0 };
    nfs41_path_fh dst_dir, dst;
    nfs41_component dst_name, *src_name;
    uint32_t depth = 0;
    int status;

    src_name = &state->file.name;

    if (rename->FileNameLength == 0) {
        /* start from state->path instead of args->path, in case we got
         * the file from a referred server */
        AcquireSRWLockShared(&state->path.lock);
        abs_path_copy(&dst_path, &state->path);
        ReleaseSRWLockShared(&state->path.lock);

        path_fh_init(&dst_dir, &dst_path);
        fh_copy(&dst_dir.fh, &state->parent.fh);

        create_silly_rename(&dst_path, &state->file.fh, &dst_name);
        dprintf(1, "silly rename: %s -> %s\n", src_name->name, dst_name.name);

        /* break any delegations and truncate before silly rename */
        nfs41_delegation_return(state->session, &state->file,
            OPEN_DELEGATE_WRITE, TRUE);

        status = nfs41_rename(state->session,
            &state->parent, src_name,
            &dst_dir, &dst_name);
        if (status) {
            dprintf(1, "nfs41_rename() failed with error %s.\n",
                nfs_error_string(status));
            status = nfs_to_windows_error(status, ERROR_ACCESS_DENIED);
        } else {
            /* rename state->path on success */
            open_state_rename(state, &dst_path);
        }
        goto out;
    }

    dst_path.len = (unsigned short)WideCharToMultiByte(CP_UTF8, 0,
        rename->FileName, rename->FileNameLength/sizeof(WCHAR),
        dst_path.path, NFS41_MAX_PATH_LEN, NULL, NULL);
    if (dst_path.len == 0) {
        eprintf("WideCharToMultiByte failed to convert destination "
            "filename %S.\n", rename->FileName);
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
            &dst_path, &dst_dir, NULL, NULL, &dst_session);
    }

    /* get the components after lookup in case a referral changed its path */
    last_component(dst_path.path, dst_path.path + dst_path.len, &dst_name);
    last_component(dst_path.path, dst_name.name, &dst_dir.name);

    if (status == NO_ERROR) {
        if (!rename->ReplaceIfExists) {
            status = ERROR_FILE_EXISTS;
            goto out;
        }
        /* break any delegations and truncate the destination file */
        nfs41_delegation_return(dst_session, &dst,
            OPEN_DELEGATE_WRITE, TRUE);
    } else if (status != ERROR_FILE_NOT_FOUND) {
        dprintf(1, "nfs41_lookup('%s') failed to find destination "
            "directory with %d\n", dst_path.path, status);
        goto out;
    }

    /* http://tools.ietf.org/html/rfc5661#section-18.26.3
     * "Source and target directories MUST reside on the same
     * file system on the server." */
    if (state->parent.fh.superblock != dst_dir.fh.superblock) {
        status = ERROR_NOT_SAME_DEVICE;
        goto out;
    }

    status = is_dst_name_opened(&dst_path, dst_session);
    if (status) {
        /* AGLO: 03/21/2011: we can't handle rename of a file with a filename 
         * that is currently opened by this client
         */
        eprintf("handle_nfs41_rename: %s is opened\n", dst_path.path);
        status = ERROR_FILE_EXISTS;
        goto out;
    }

    /* break any delegations on the source file */
    nfs41_delegation_return(state->session, &state->file,
        OPEN_DELEGATE_WRITE, FALSE);

    status = nfs41_rename(state->session,
        &state->parent, src_name,
        &dst_dir, &dst_name);
    if (status) {
        dprintf(1, "nfs41_rename() failed with error %s.\n",
            nfs_error_string(status));
        status = nfs_to_windows_error(status, ERROR_ACCESS_DENIED);
    } else {
        /* rename state->path on success */
        open_state_rename(state, &dst_path);
    }
out:
    return status;
}