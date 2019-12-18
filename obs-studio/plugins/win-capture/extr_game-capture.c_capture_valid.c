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
struct game_capture {int /*<<< orphan*/  target_process; int /*<<< orphan*/  window; int /*<<< orphan*/  dwm_capture; } ;

/* Variables and functions */
 int /*<<< orphan*/  IsWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  object_signalled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool capture_valid(struct game_capture *gc)
{
	if (!gc->dwm_capture && !IsWindow(gc->window))
		return false;

	return !object_signalled(gc->target_process);
}