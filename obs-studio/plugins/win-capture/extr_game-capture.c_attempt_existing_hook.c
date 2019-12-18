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
struct TYPE_2__ {int /*<<< orphan*/  executable; } ;
struct game_capture {scalar_t__ hook_restart; TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_CAPTURE_RESTART ; 
 int /*<<< orphan*/  SetEvent (scalar_t__) ; 
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ open_event_gc (struct game_capture*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool attempt_existing_hook(struct game_capture *gc)
{
	gc->hook_restart = open_event_gc(gc, EVENT_CAPTURE_RESTART);
	if (gc->hook_restart) {
		debug("existing hook found, signaling process: %s",
		      gc->config.executable);
		SetEvent(gc->hook_restart);
		return true;
	}

	return false;
}