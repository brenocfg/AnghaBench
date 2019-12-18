#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  raw_active; int /*<<< orphan*/  gpu_refs; } ;
typedef  TYPE_1__ video_t ;

/* Variables and functions */
 int /*<<< orphan*/  log_skipped (TYPE_1__*) ; 
 scalar_t__ os_atomic_dec_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_atomic_load_bool (int /*<<< orphan*/ *) ; 

void video_output_dec_texture_encoders(video_t *video)
{
	if (os_atomic_dec_long(&video->gpu_refs) == 0 &&
	    !os_atomic_load_bool(&video->raw_active)) {
		log_skipped(video);
	}
}