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
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  THREAD_ALL_ACCESS ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 
 scalar_t__ w32_OpenThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HANDLE w32_open_thread(int pid, int tid) {
	HANDLE thread = w32_OpenThread (THREAD_ALL_ACCESS, 0, tid);
	if (thread == INVALID_HANDLE_VALUE) {
		r_sys_perror ("w32_open_thread/OpenThread");
	}
	return thread;
}