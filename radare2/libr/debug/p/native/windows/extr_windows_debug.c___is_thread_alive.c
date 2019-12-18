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
struct TYPE_3__ {int bFinished; int /*<<< orphan*/  hThread; } ;
typedef  int /*<<< orphan*/  RDebug ;
typedef  TYPE_1__* PTHREAD_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  ResumeThread (int /*<<< orphan*/ ) ; 
 int SuspendThread (int /*<<< orphan*/ ) ; 
 TYPE_1__* __find_thread (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool __is_thread_alive(RDebug *dbg, int tid) {
	PTHREAD_ITEM th = __find_thread (dbg, tid);
	if (!th) {
		return false;
	}
	if (!th->bFinished) {
		if (SuspendThread (th->hThread) != -1) {
			ResumeThread (th->hThread);
			return true;
		}
	}
	th->bFinished = true;
	return false;
}