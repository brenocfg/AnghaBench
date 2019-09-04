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
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int ptw32_cancelable_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
pthreadCancelableTimedWait (HANDLE waitHandle, DWORD timeout)
{
  return (ptw32_cancelable_wait (waitHandle, timeout));
}