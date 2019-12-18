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
struct game_capture_config {scalar_t__ mode; scalar_t__ priority; scalar_t__ force_scaling; scalar_t__ scale_cx; scalar_t__ scale_cy; scalar_t__ force_shmem; scalar_t__ limit_framerate; scalar_t__ capture_overlays; int /*<<< orphan*/  executable; int /*<<< orphan*/  title; int /*<<< orphan*/  class; } ;

/* Variables and functions */
 scalar_t__ CAPTURE_MODE_WINDOW ; 
 scalar_t__ s_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool capture_needs_reset(struct game_capture_config *cfg1,
				       struct game_capture_config *cfg2)
{
	if (cfg1->mode != cfg2->mode) {
		return true;

	} else if (cfg1->mode == CAPTURE_MODE_WINDOW &&
		   (s_cmp(cfg1->class, cfg2->class) != 0 ||
		    s_cmp(cfg1->title, cfg2->title) != 0 ||
		    s_cmp(cfg1->executable, cfg2->executable) != 0 ||
		    cfg1->priority != cfg2->priority)) {
		return true;

	} else if (cfg1->force_scaling != cfg2->force_scaling) {
		return true;

	} else if (cfg1->force_scaling && (cfg1->scale_cx != cfg2->scale_cx ||
					   cfg1->scale_cy != cfg2->scale_cy)) {
		return true;

	} else if (cfg1->force_shmem != cfg2->force_shmem) {
		return true;

	} else if (cfg1->limit_framerate != cfg2->limit_framerate) {
		return true;

	} else if (cfg1->capture_overlays != cfg2->capture_overlays) {
		return true;
	}

	return false;
}