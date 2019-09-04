#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stateid_arg ;
struct TYPE_10__ {int /*<<< orphan*/  ctime; TYPE_3__* state; int /*<<< orphan*/  buf; } ;
typedef  TYPE_2__ setattr_upcall_args ;
struct TYPE_11__ {int /*<<< orphan*/  lock; scalar_t__ pnfs_last_offset; int /*<<< orphan*/  file; int /*<<< orphan*/  session; } ;
typedef  TYPE_3__ nfs41_open_state ;
struct TYPE_9__ {int count; int /*<<< orphan*/ * arr; } ;
struct TYPE_12__ {int /*<<< orphan*/  change; scalar_t__ size; TYPE_1__ attrmask; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ nfs41_file_info ;
struct TYPE_13__ {scalar_t__ QuadPart; } ;
typedef  TYPE_5__* PLARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  AcquireSRWLockExclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FATTR4_WORD0_SIZE ; 
 int /*<<< orphan*/  OPEN_DELEGATE_READ ; 
 int /*<<< orphan*/  ReleaseSRWLockExclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintf (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  nfs41_delegation_return (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs41_open_stateid_arg (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int nfs41_setattr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ nfs_error_string (int) ; 
 int nfs_to_windows_error (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_nfs41_set_size(setattr_upcall_args *args)
{
    nfs41_file_info info = { 0 };
    stateid_arg stateid;
    /* note: this is called with either FILE_END_OF_FILE_INFO or
     * FILE_ALLOCATION_INFO, both of which contain a single LARGE_INTEGER */
    PLARGE_INTEGER size = (PLARGE_INTEGER)args->buf;
    nfs41_open_state *state = args->state;
    int status;

    /* break read delegations before SETATTR */
    nfs41_delegation_return(state->session, &state->file,
        OPEN_DELEGATE_READ, FALSE);

    nfs41_open_stateid_arg(state, &stateid);

    info.size = size->QuadPart;
    info.attrmask.count = 1;
    info.attrmask.arr[0] = FATTR4_WORD0_SIZE;

    dprintf(2, "calling setattr() with size=%lld\n", info.size);
    status = nfs41_setattr(state->session, &state->file, &stateid, &info);
    if (status) {
        dprintf(1, "nfs41_setattr() failed with error %s.\n",
            nfs_error_string(status));
        goto out;
    }

    /* update the last offset for LAYOUTCOMMIT */
    AcquireSRWLockExclusive(&state->lock);
    state->pnfs_last_offset = info.size ? info.size - 1 : 0;
    ReleaseSRWLockExclusive(&state->lock);
    args->ctime = info.change;
out:
    return status = nfs_to_windows_error(status, ERROR_NOT_SUPPORTED);
}