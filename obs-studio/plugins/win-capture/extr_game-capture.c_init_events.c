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
struct game_capture {void* hook_exit; void* hook_ready; void* hook_init; void* hook_stop; void* hook_restart; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_CAPTURE_RESTART ; 
 int /*<<< orphan*/  EVENT_CAPTURE_STOP ; 
 int /*<<< orphan*/  EVENT_HOOK_EXIT ; 
 int /*<<< orphan*/  EVENT_HOOK_INIT ; 
 int /*<<< orphan*/  EVENT_HOOK_READY ; 
 int /*<<< orphan*/  GetLastError () ; 
 void* open_event_gc (struct game_capture*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool init_events(struct game_capture *gc)
{
	if (!gc->hook_restart) {
		gc->hook_restart = open_event_gc(gc, EVENT_CAPTURE_RESTART);
		if (!gc->hook_restart) {
			warn("init_events: failed to get hook_restart "
			     "event: %lu",
			     GetLastError());
			return false;
		}
	}

	if (!gc->hook_stop) {
		gc->hook_stop = open_event_gc(gc, EVENT_CAPTURE_STOP);
		if (!gc->hook_stop) {
			warn("init_events: failed to get hook_stop event: %lu",
			     GetLastError());
			return false;
		}
	}

	if (!gc->hook_init) {
		gc->hook_init = open_event_gc(gc, EVENT_HOOK_INIT);
		if (!gc->hook_init) {
			warn("init_events: failed to get hook_init event: %lu",
			     GetLastError());
			return false;
		}
	}

	if (!gc->hook_ready) {
		gc->hook_ready = open_event_gc(gc, EVENT_HOOK_READY);
		if (!gc->hook_ready) {
			warn("init_events: failed to get hook_ready event: %lu",
			     GetLastError());
			return false;
		}
	}

	if (!gc->hook_exit) {
		gc->hook_exit = open_event_gc(gc, EVENT_HOOK_EXIT);
		if (!gc->hook_exit) {
			warn("init_events: failed to get hook_exit event: %lu",
			     GetLastError());
			return false;
		}
	}

	return true;
}