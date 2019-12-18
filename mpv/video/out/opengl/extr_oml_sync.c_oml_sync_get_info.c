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
struct vo_vsync_info {int /*<<< orphan*/  last_queue_display_time; int /*<<< orphan*/  skipped_vsyncs; int /*<<< orphan*/  vsync_duration; } ;
struct oml_sync {int /*<<< orphan*/  last_queue_display_time; int /*<<< orphan*/  last_skipped_vsyncs; int /*<<< orphan*/  vsync_duration; int /*<<< orphan*/  state_ok; } ;

/* Variables and functions */
 int /*<<< orphan*/  oml_sync_reset (struct oml_sync*) ; 

void oml_sync_get_info(struct oml_sync *oml, struct vo_vsync_info *info)
{
    if (!oml->state_ok)
        oml_sync_reset(oml);
    info->vsync_duration = oml->vsync_duration;
    info->skipped_vsyncs = oml->last_skipped_vsyncs;
    info->last_queue_display_time = oml->last_queue_display_time;
}