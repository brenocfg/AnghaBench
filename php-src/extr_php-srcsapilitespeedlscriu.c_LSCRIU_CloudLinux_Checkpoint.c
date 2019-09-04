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
 int /*<<< orphan*/  LSAPI_reset_server_state () ; 
 int /*<<< orphan*/  LSCRIU_Set_Initial_Start_Reqs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSCRIU_Wink_Server_is_Ready () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  getppid () ; 
 int /*<<< orphan*/  lscriu_dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lscriu_err (char*,int /*<<< orphan*/ ,...) ; 
 int s_lscapi_dump_me () ; 
 int /*<<< orphan*/  s_native ; 
 int /*<<< orphan*/  s_pid ; 
 int s_restored ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void LSCRIU_CloudLinux_Checkpoint(void)
{
    int iRet;

    if ((!s_native) && (!s_lscapi_dump_me)) {
        lscriu_dbg("LSCRIU (%d): Not native and unable to dump - abandon one-time "
                   "dump\n", s_pid);
        return;
    }

    iRet = s_lscapi_dump_me();
    if (iRet < 0) {
        lscriu_err("LSCRIU: CloudLinux dump of PID: %d, error: %s\n",
                   s_pid, strerror(errno));
    }
    if (iRet == 0) {
        // Dumped.  To continue the child must send us the handles back
        lscriu_err("LSCRIU: Successful CloudLinux dump of PID: %d\n", s_pid);
    }
    else {
        s_restored = 1;
        LSAPI_reset_server_state();
        /*
         Here we have restored the php process, so we should to tell (via
         semaphore) mod_lsapi that we are started and ready to receive data.
        */
        LSCRIU_Wink_Server_is_Ready();
        lscriu_err("LSCRIU: Successful CloudLinux restore of PID: %d, parent: %d.\n",
                   getpid(), getppid());
    }
    LSCRIU_Set_Initial_Start_Reqs(0);
}