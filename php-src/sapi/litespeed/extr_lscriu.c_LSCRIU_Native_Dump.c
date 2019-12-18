#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_4__ {int /*<<< orphan*/  m_chSocketDir; int /*<<< orphan*/  m_chImageDirectory; int /*<<< orphan*/  m_iPidToDump; } ;
typedef  TYPE_1__ criu_native_dump_t ;
typedef  int /*<<< orphan*/  criu_native_dump ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  lscriu_dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lscriu_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_pid ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 char* strrchr (int /*<<< orphan*/ ,char) ; 
 int write (int,TYPE_1__*,int) ; 

__attribute__((used)) static int LSCRIU_Native_Dump(pid_t iPid,
                              char  *pchImagePath,
                              int   iFdNative) {
    criu_native_dump_t criu_native_dump;
    char *pchLastSlash;

    memset(&criu_native_dump, 0, sizeof(criu_native_dump));
    criu_native_dump.m_iPidToDump = iPid;
    strncpy(criu_native_dump.m_chImageDirectory, pchImagePath,
            sizeof(criu_native_dump.m_chImageDirectory));
    pchLastSlash = strrchr(criu_native_dump.m_chSocketDir,'/');
    if (pchLastSlash) {
        pchLastSlash++;
        (*pchLastSlash) = 0;
    }
    lscriu_dbg("LSCRIU (%d): Sent the dump request to the listener\n", s_pid);
    if (write(iFdNative,
              &criu_native_dump,
              sizeof(criu_native_dump)) == -1) {
        lscriu_err("LSCRIU (%d): Error sending dump request to the listener: %s\n",
                   s_pid, strerror(errno));
        return(-1);
    }
    return 0;
}