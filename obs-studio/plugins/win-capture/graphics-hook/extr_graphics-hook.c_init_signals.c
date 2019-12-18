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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_CAPTURE_RESTART ; 
 int /*<<< orphan*/  EVENT_CAPTURE_STOP ; 
 int /*<<< orphan*/  EVENT_HOOK_EXIT ; 
 int /*<<< orphan*/  EVENT_HOOK_INIT ; 
 int /*<<< orphan*/  EVENT_HOOK_READY ; 
 int /*<<< orphan*/  GetCurrentProcessId () ; 
 void* init_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* signal_exit ; 
 void* signal_init ; 
 void* signal_ready ; 
 void* signal_restart ; 
 void* signal_stop ; 

__attribute__((used)) static inline bool init_signals(void)
{
	DWORD pid = GetCurrentProcessId();

	signal_restart = init_event(EVENT_CAPTURE_RESTART, pid);
	if (!signal_restart) {
		return false;
	}

	signal_stop = init_event(EVENT_CAPTURE_STOP, pid);
	if (!signal_stop) {
		return false;
	}

	signal_ready = init_event(EVENT_HOOK_READY, pid);
	if (!signal_ready) {
		return false;
	}

	signal_exit = init_event(EVENT_HOOK_EXIT, pid);
	if (!signal_exit) {
		return false;
	}

	signal_init = init_event(EVENT_HOOK_INIT, pid);
	if (!signal_init) {
		return false;
	}

	return true;
}