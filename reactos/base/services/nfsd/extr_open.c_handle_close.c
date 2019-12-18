#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ srv_open; scalar_t__ renamed; scalar_t__ remove; } ;
struct TYPE_16__ {TYPE_5__ close; } ;
struct TYPE_17__ {TYPE_3__* state_ref; TYPE_1__ args; } ;
typedef  TYPE_2__ nfs41_upcall ;
struct TYPE_15__ {int /*<<< orphan*/  fileid; } ;
struct TYPE_19__ {int /*<<< orphan*/  name; } ;
struct TYPE_21__ {TYPE_12__ fh; TYPE_4__ name; } ;
struct TYPE_18__ {scalar_t__ type; scalar_t__ srv_open; scalar_t__ do_close; TYPE_8__ file; int /*<<< orphan*/  parent; int /*<<< orphan*/  session; int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ nfs41_open_state ;
typedef  TYPE_4__ nfs41_component ;
typedef  TYPE_5__ close_upcall_args ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INTERNAL_ERROR ; 
 scalar_t__ NF4REG ; 
 int NFS4ERR_FILE_OPEN ; 
 int NFS4_OK ; 
 int /*<<< orphan*/  OPEN_DELEGATE_WRITE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  client_state_remove (TYPE_3__*) ; 
 int /*<<< orphan*/  create_silly_rename (int /*<<< orphan*/ *,TYPE_12__*,TYPE_4__*) ; 
 int do_nfs41_close (TYPE_3__*) ; 
 int /*<<< orphan*/  dprintf (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs41_delegation_remove_srvopen (int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  nfs41_delegation_return (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs41_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_error_string (int) ; 
 int nfs_to_windows_error (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_layout_state_close (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static int handle_close(nfs41_upcall *upcall)
{
    int status = NFS4_OK, rm_status = NFS4_OK;
    close_upcall_args *args = &upcall->args.close;
    nfs41_open_state *state = upcall->state_ref;

    /* return associated file layouts if necessary */
    if (state->type == NF4REG)
        pnfs_layout_state_close(state->session, state, args->remove);

    if (state->srv_open == args->srv_open)
        nfs41_delegation_remove_srvopen(state->session, &state->file);

    if (args->remove) {
        nfs41_component *name = &state->file.name;

        if (args->renamed) {
            dprintf(1, "removing a renamed file %s\n", name->name);
            create_silly_rename(&state->path, &state->file.fh, name);
            status = do_nfs41_close(state);
            if (status)
                goto out;
            else
                state->do_close = 0;
        }

        /* break any delegations and truncate before REMOVE */
        nfs41_delegation_return(state->session, &state->file,
            OPEN_DELEGATE_WRITE, TRUE);

		dprintf(1, "calling nfs41_remove for %s\n", name->name);
retry_delete:
        rm_status = nfs41_remove(state->session, &state->parent,
            name, state->file.fh.fileid);
        if (rm_status) {
			if (rm_status == NFS4ERR_FILE_OPEN) {
				status = do_nfs41_close(state);
				if (!status) {
					state->do_close = 0;
					goto retry_delete;
				}  else goto out;
			}
            dprintf(1, "nfs41_remove() failed with error %s.\n",
                nfs_error_string(rm_status));
            rm_status = nfs_to_windows_error(rm_status, ERROR_INTERNAL_ERROR);
        }
    }

    if (state->do_close) {
        status = do_nfs41_close(state);
    }
out:
    /* remove from the client's list of state for recovery */
    client_state_remove(state);

    if (status || !rm_status)
        return status;
    else
        return rm_status;
}