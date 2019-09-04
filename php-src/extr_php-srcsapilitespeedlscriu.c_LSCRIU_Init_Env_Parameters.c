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
typedef  scalar_t__ GlobalCounterType_t ;

/* Variables and functions */
 scalar_t__ CRIU_GCOUNTER_PIPE ; 
 scalar_t__ CRIU_GCOUNTER_SHM ; 
 scalar_t__ CRIU_GCOUNTER_SIG ; 
 scalar_t__ LSAPI_Is_Listen () ; 
 int /*<<< orphan*/  LSCRIU_Set_Global_Counter_Type (scalar_t__) ; 
 int /*<<< orphan*/  LSCRIU_Set_Initial_Start_Reqs (int) ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int atoi (char const*) ; 
 void* getenv (char*) ; 
 int /*<<< orphan*/  getpid () ; 
 int init_native_env () ; 
 int /*<<< orphan*/  lsapi_criu_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsapi_siguser2 ; 
 int /*<<< orphan*/  lscriu_dbg (char*,int /*<<< orphan*/ ,...) ; 
 int s_native ; 

__attribute__((used)) static int LSCRIU_Init_Env_Parameters(void)
{
    const char *p;
    int n;

    p = getenv("LSAPI_INITIAL_START");
    if (!p)
        p = getenv("LSAPI_BACKEND_INITIAL_START");
    if (p) {
        n = atoi(p);

        if (n > 0) {
            lscriu_dbg("LSCRIU (%d): Set start requests based on environment (%d)\n",
                       getpid(), n);
            LSCRIU_Set_Initial_Start_Reqs(n);
        } else {
            lscriu_dbg("LSCRIU (%d): LSAPI_INITIAL_START set to 0 disabled\n",
                       getpid());
            return 0;
        }
    } else {
        lscriu_dbg("LSCRIU (%d): LSAPI_INITIAL_START NOT set - disabled\n",
                   getpid());
        return 0;
    }
    if (LSAPI_Is_Listen()) {
        lscriu_dbg("LSCRIU (%d): Listening...\n", getpid());
        GlobalCounterType_t gc_type = CRIU_GCOUNTER_SHM;
        char *env;
        if ((env = getenv("LSAPI_CRIU_USE_SHM"))) {
            // CloudLinux doc: Off (shared memory) or Signals.
            // Litespeed doc: On (shared memory) or Signals
            // So just check the first character for an 'S' and if not, then
            // use shared memory.  Pipe support is lost (sigh).
            if ((*env == 'S') || (*env == 's'))
                gc_type = CRIU_GCOUNTER_SIG; // Just assume the rest is signals
            // else use the default of shared memory
        }
        else if ((env = getenv("LSAPI_SIGNALS"))) {
            if ((*env == '1') ||
                (*env == 'Y') ||
                (*env == 'y') ||
                (*env == 'T') ||
                (*env == 't') ||
                (((*env == 'O') || (*env == 'o')) &&
                 ((*(env + 1) == 'N') || (*(env + 1) == 'n'))))
                gc_type = CRIU_GCOUNTER_SIG;
            else if (*env == 2)
                gc_type = CRIU_GCOUNTER_PIPE; // The only case for pipe
            //else use the default of shared memory
        }
        if (gc_type != CRIU_GCOUNTER_SHM) {
            lscriu_dbg("LSCRIU (%d): Use %s\n", getpid(),
                       gc_type == CRIU_GCOUNTER_SIG ? "signals" : "pipe");
            lsapi_criu_signal(SIGUSR2, lsapi_siguser2);
        }
        else
            lscriu_dbg("LSCRIU (%d): Use shared memory\n", getpid());
        LSCRIU_Set_Global_Counter_Type(gc_type);
    }
    else
        lscriu_dbg("LSCRIU (%d): NOT Listening\n", getpid());

    char *criu_mode = NULL;
    criu_mode = getenv("LSAPI_CRIU");
    // 0 disabled
    // 1 cloudlinux
    // 2 native
    if (criu_mode) {
        if (*criu_mode == '0') {
             lscriu_dbg("LSCRIU (%d): Disabled by environment.\n", getpid());
             LSCRIU_Set_Initial_Start_Reqs(0);
        }
        else if (*criu_mode == '2') {
            lscriu_dbg("LSCRIU (%d): Disabled by environment.\n", getpid());
            s_native = 1;
        }
    }

    if (s_native && init_native_env() == -1)
        LSCRIU_Set_Initial_Start_Reqs(0);

    //unset_lsapi_envs();
    return 0;
}