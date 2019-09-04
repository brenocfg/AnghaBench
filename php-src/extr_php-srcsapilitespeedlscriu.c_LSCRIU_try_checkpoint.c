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
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  LSAPI_reset_server_state () ; 
 int /*<<< orphan*/  LSCRIU_CloudLinux_Checkpoint () ; 
 int LSCRIU_Native_Dump (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSCRIU_Restored_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LSCRIU_Set_Initial_Start_Reqs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSCRIU_Wait_Dump_Finsh_Or_Restored (int) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int fork () ; 
 int getpid () ; 
 int getppid () ; 
 int /*<<< orphan*/  lscriu_dbg (char*,int) ; 
 int /*<<< orphan*/  lscriu_err (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_criu_image_path ; 
 int /*<<< orphan*/  s_fd_native ; 
 int /*<<< orphan*/  s_native ; 
 int s_restored ; 
 int s_tried_checkpoint ; 
 int /*<<< orphan*/  setsid () ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void LSCRIU_try_checkpoint(int *forked_pid)
{
    int iRet;
    pid_t iPid;
    pid_t iPidDump = getpid();

    if (s_tried_checkpoint) {
        lscriu_dbg("LSCRIU (%d): Already tried checkpoint - one time per customer\n",
                   iPidDump);
        return;
    }
    lscriu_dbg("LSCRIU (%d): Trying checkpoint\n", iPidDump);
    s_tried_checkpoint = 1;
    if (!s_native) {
        LSCRIU_CloudLinux_Checkpoint();
        return;
    }

    lscriu_dbg("LSCRIU (%d): fork!\n", iPidDump);
    iPid = fork();
    if (iPid < 0) {
        lscriu_err("LSCRIU (%d): Can't checkpoint due to a fork error: %s\n",
                   iPidDump, strerror(errno));
        return;
    }
    if (iPid == 0) {
        pid_t   iPidParent = getppid();

        setsid();
        iRet = LSCRIU_Native_Dump(iPidDump,
                                  s_criu_image_path,
                                  s_fd_native);
        close(s_fd_native);

        LSCRIU_Wait_Dump_Finsh_Or_Restored(iPidParent);
        LSCRIU_Restored_Error(0, "Restored!");
        LSAPI_reset_server_state();
        s_restored = 1;
    }
    else {
        if (forked_pid)
            *forked_pid = iPid;
    }
    LSCRIU_Set_Initial_Start_Reqs(0);
}