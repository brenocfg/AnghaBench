#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omap_dss_device {int dummy; } ;
struct TYPE_3__ {int display_enabled; int /*<<< orphan*/  lock; int /*<<< orphan*/  audio_playing_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 TYPE_1__ hdmi ; 
 int /*<<< orphan*/  hdmi_power_off_full (struct omap_dss_device*) ; 
 int /*<<< orphan*/  hdmi_stop_audio_stream (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hdmi_display_disable(struct omap_dss_device *dssdev)
{
	unsigned long flags;

	DSSDBG("Enter hdmi_display_disable\n");

	mutex_lock(&hdmi.lock);

	spin_lock_irqsave(&hdmi.audio_playing_lock, flags);
	hdmi_stop_audio_stream(&hdmi);
	hdmi.display_enabled = false;
	spin_unlock_irqrestore(&hdmi.audio_playing_lock, flags);

	hdmi_power_off_full(dssdev);

	mutex_unlock(&hdmi.lock);
}