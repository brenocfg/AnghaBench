#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stateid_arg ;
struct TYPE_15__ {int /*<<< orphan*/  ctime; int /*<<< orphan*/  mode; int /*<<< orphan*/  buf; } ;
typedef  TYPE_3__ setexattr_upcall_args ;
struct TYPE_13__ {TYPE_3__ setexattr; } ;
struct TYPE_16__ {TYPE_5__* state_ref; TYPE_1__ args; } ;
typedef  TYPE_4__ nfs41_upcall ;
struct TYPE_17__ {int /*<<< orphan*/  file; int /*<<< orphan*/  session; } ;
typedef  TYPE_5__ nfs41_open_state ;
struct TYPE_14__ {int count; scalar_t__* arr; } ;
struct TYPE_18__ {int /*<<< orphan*/  change; TYPE_2__ attrmask; int /*<<< orphan*/  mode; } ;
typedef  TYPE_6__ nfs41_file_info ;
struct TYPE_19__ {int EaNameLength; int /*<<< orphan*/  EaName; } ;
typedef  TYPE_7__* PFILE_FULL_EA_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FATTR4_WORD1_MODE ; 
 int /*<<< orphan*/  OPEN_DELEGATE_READ ; 
 int /*<<< orphan*/  dprintf (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs41_delegation_return (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs41_ea_set (TYPE_5__*,TYPE_7__*) ; 
 int /*<<< orphan*/  nfs41_open_stateid_arg (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int nfs41_setattr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  nfs_error_string (int) ; 
 int nfs_to_windows_error (int,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int handle_setexattr(nfs41_upcall *upcall)
{
    int status;
    setexattr_upcall_args *args = &upcall->args.setexattr;
    nfs41_open_state *state = upcall->state_ref;
    PFILE_FULL_EA_INFORMATION ea = 
        (PFILE_FULL_EA_INFORMATION)args->buf;

    /* break read delegations before SETATTR */
    nfs41_delegation_return(state->session, &state->file,
        OPEN_DELEGATE_READ, FALSE);

    if (strncmp("NfsV3Attributes", ea->EaName, ea->EaNameLength) == 0
            && sizeof("NfsV3Attributes")-1 == ea->EaNameLength) {
        nfs41_file_info info;
        stateid_arg stateid;

        nfs41_open_stateid_arg(state, &stateid);

        info.mode = args->mode;
        info.attrmask.arr[0] = 0;
        info.attrmask.arr[1] = FATTR4_WORD1_MODE;
        info.attrmask.count = 2;

        status = nfs41_setattr(state->session, &state->file, &stateid, &info);
        if (status) {
            dprintf(1, "nfs41_setattr() failed with error %s.\n",
                nfs_error_string(status));
            goto out;
        }

        args->ctime = info.change;
        goto out;
    }

    status = nfs41_ea_set(state, ea);
out:
    return nfs_to_windows_error(status, ERROR_NOT_SUPPORTED);
}