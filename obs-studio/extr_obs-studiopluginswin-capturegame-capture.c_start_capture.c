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
struct game_capture {TYPE_1__* global_hook_info; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CAPTURE_TYPE_MEMORY ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  init_shmem_capture (struct game_capture*) ; 
 int /*<<< orphan*/  init_shtex_capture (struct game_capture*) ; 

__attribute__((used)) static bool start_capture(struct game_capture *gc)
{
	debug("Starting capture");

	if (gc->global_hook_info->type == CAPTURE_TYPE_MEMORY) {
		if (!init_shmem_capture(gc)) {
			return false;
		}

		info("memory capture successful");
	} else {
		if (!init_shtex_capture(gc)) {
			return false;
		}

		info("shared texture capture successful");
	}

	return true;
}