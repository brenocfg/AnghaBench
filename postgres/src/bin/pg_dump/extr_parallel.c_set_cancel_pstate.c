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
struct TYPE_2__ {int /*<<< orphan*/ * pstate; } ;
typedef  int /*<<< orphan*/  ParallelState ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 TYPE_1__ signal_info ; 
 int /*<<< orphan*/  signal_info_lock ; 

__attribute__((used)) static void
set_cancel_pstate(ParallelState *pstate)
{
#ifdef WIN32
	EnterCriticalSection(&signal_info_lock);
#endif

	signal_info.pstate = pstate;

#ifdef WIN32
	LeaveCriticalSection(&signal_info_lock);
#endif
}