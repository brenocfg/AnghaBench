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
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  EPERM ; 
 int ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  ESRCH ; 
 scalar_t__ GetCurrentProcessId () ; 
 int GetLastError () ; 
 int /*<<< orphan*/ * OpenProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCESS_SET_INFORMATION ; 
 int /*<<< orphan*/  PTW32_FALSE ; 
 int SCHED_OTHER ; 
 int /*<<< orphan*/  errno ; 

int
sched_setscheduler (pid_t pid, int policy)
{
  /*
   * Win32 only has one policy which we call SCHED_OTHER.
   * However, we try to provide other valid side-effects
   * such as EPERM and ESRCH errors. Choosing to check
   * for a valid policy last allows us to get the most value out
   * of this function.
   */
  if (0 != pid)
    {
      int selfPid = (int) GetCurrentProcessId ();

      if (pid != selfPid)
	{
	  HANDLE h =
	    OpenProcess (PROCESS_SET_INFORMATION, PTW32_FALSE, (DWORD) pid);

	  if (NULL == h)
	    {
	      errno =
		(GetLastError () ==
		 (0xFF & ERROR_ACCESS_DENIED)) ? EPERM : ESRCH;
	      return -1;
	    }
	  else
	    CloseHandle(h);
	}
    }

  if (SCHED_OTHER != policy)
    {
      errno = ENOSYS;
      return -1;
    }

  /*
   * Don't set anything because there is nothing to set.
   * Just return the current (the only possible) value.
   */
  return SCHED_OTHER;
}