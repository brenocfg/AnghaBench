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
struct oml_sync {int vsync_duration; int last_skipped_vsyncs; int last_queue_display_time; } ;

/* Variables and functions */

__attribute__((used)) static void oml_sync_reset(struct oml_sync *oml)
{
    oml->vsync_duration = -1;
    oml->last_skipped_vsyncs = -1;
    oml->last_queue_display_time = -1;
}