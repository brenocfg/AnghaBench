#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ CRIU_GCOUNTER_SHM ; 
 int /*<<< orphan*/  LSAPI_Get_ppid () ; 
 scalar_t__ LSCRIU_Get_Global_Counter_Type () ; 
 int /*<<< orphan*/  LSCRIU_Increase_Global_Counter () ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lscriu_dbg (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ s_initial_start_reqs ; 
 scalar_t__ s_requests_count ; 

void LSCRIU_inc_req_procssed()
{
    if (!LSCRIU_Get_Global_Counter_Type()) {
        ++s_requests_count;
    }

    lscriu_dbg("LSCRIU (%d): s_requests_count %d counter %d\n", getpid(),
               s_requests_count, s_initial_start_reqs);

    if (s_initial_start_reqs > 0 && s_requests_count <= s_initial_start_reqs) {
        if (LSCRIU_Get_Global_Counter_Type() == CRIU_GCOUNTER_SHM) {
            LSCRIU_Increase_Global_Counter();
            if (s_requests_count >= s_initial_start_reqs) {
                //Maybe this time we can stop to send signal and wait for
                //1 second of select timeout
                //kill( LSCRIU_Get_ppid(), SIGUSR2 );
                lscriu_dbg("LSCRIU (%d): Time to dump main process with semaphore\n",
                           getpid());
            }
        } else {
            kill(LSAPI_Get_ppid(), SIGUSR2);
            lscriu_dbg("LSCRIU (%d): Send kill to main process with signals\n",
                       getpid());
        }
    }
}