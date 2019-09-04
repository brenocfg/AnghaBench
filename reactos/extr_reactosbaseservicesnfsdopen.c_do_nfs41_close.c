#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  stateid; int /*<<< orphan*/  type; int /*<<< orphan*/ * delegation; TYPE_2__* open; } ;
typedef  TYPE_1__ stateid_arg ;
typedef  int /*<<< orphan*/  stateid4 ;
struct TYPE_6__ {int /*<<< orphan*/  file; int /*<<< orphan*/  session; int /*<<< orphan*/  stateid; } ;
typedef  TYPE_2__ nfs41_open_state ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  STATEID_OPEN ; 
 int /*<<< orphan*/  dprintf (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int nfs41_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_error_string (int) ; 
 int nfs_to_windows_error (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_nfs41_close(nfs41_open_state *state)
{
    int status;
    stateid_arg stateid;
    stateid.open = state;
    stateid.delegation = NULL;
    stateid.type = STATEID_OPEN;
    memcpy(&stateid.stateid, &state->stateid, sizeof(stateid4));

    status = nfs41_close(state->session, &state->file, &stateid);
    if (status) {
        dprintf(1, "nfs41_close() failed with error %s.\n",
            nfs_error_string(status));
        status = nfs_to_windows_error(status, ERROR_INTERNAL_ERROR);
    }

    return status;
}