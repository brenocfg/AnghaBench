#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int in_recovery; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; } ;
typedef  TYPE_1__ nfs41_rpc_clnt ;
typedef  int bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  AcquireSRWLockExclusive (int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  ReleaseSRWLockExclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (int,char*,int) ; 

__attribute__((used)) static bool_t rpc_renew_in_progress(nfs41_rpc_clnt *rpc, int *value)
{
    bool_t status = FALSE;
    AcquireSRWLockExclusive(&rpc->lock);
    if (value) {
        dprintf(1, "nfs41_rpc_renew_in_progress: setting value %d\n", *value);
        rpc->in_recovery = *value;
        if (!rpc->in_recovery) 
            SetEvent(rpc->cond);
    } else {
        status = rpc->in_recovery;
        dprintf(1, "nfs41_rpc_renew_in_progress: returning value %d\n", status);
    }
    ReleaseSRWLockExclusive(&rpc->lock);
    return status;
}