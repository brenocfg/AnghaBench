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
struct game_capture {int /*<<< orphan*/  target_process; int /*<<< orphan*/  app_sid; scalar_t__ is_app; int /*<<< orphan*/  process_is_64bit; TYPE_1__ config; int /*<<< orphan*/  process_id; } ;

/* Variables and functions */
 int PROCESS_QUERY_INFORMATION ; 
 int SYNCHRONIZE ; 
 int /*<<< orphan*/  get_app_sid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_64bit_process (int /*<<< orphan*/ ) ; 
 scalar_t__ is_app (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_process (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool open_target_process(struct game_capture *gc)
{
	gc->target_process = open_process(
		PROCESS_QUERY_INFORMATION | SYNCHRONIZE, false, gc->process_id);
	if (!gc->target_process) {
		warn("could not open process: %s", gc->config.executable);
		return false;
	}

	gc->process_is_64bit = is_64bit_process(gc->target_process);
	gc->is_app = is_app(gc->target_process);
	if (gc->is_app) {
		gc->app_sid = get_app_sid(gc->target_process);
	}
	return true;
}