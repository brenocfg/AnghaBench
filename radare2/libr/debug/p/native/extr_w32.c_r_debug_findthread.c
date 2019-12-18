#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_2__ {int tid; int pid; } ;
typedef  int /*<<< orphan*/  THREAD_ITEM ;
typedef  TYPE_1__* PTHREAD_ITEM ;

/* Variables and functions */
 scalar_t__ lstThread ; 

__attribute__((used)) static void * r_debug_findthread (int pid, int tid) {
	PTHREAD_ITEM threadPtr = NULL;
	if (lstThread) {
		threadPtr = (PTHREAD_ITEM)lstThread;
		while (threadPtr->tid != 0) {
			if (threadPtr->pid == pid) {
				if (threadPtr->tid == tid) {
					return ((void*)threadPtr);
				}
			}
			threadPtr = (PTHREAD_ITEM)((ULONG_PTR)threadPtr + sizeof (THREAD_ITEM));
		}
	}
	return NULL;
}