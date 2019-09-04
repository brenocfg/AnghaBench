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
struct omap_hdmi {int audio_configured; int audio_playing; int /*<<< orphan*/  lock; int /*<<< orphan*/ * audio_abort_cb; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct omap_hdmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdmi_audio_shutdown(struct device *dev)
{
	struct omap_hdmi *hd = dev_get_drvdata(dev);

	mutex_lock(&hd->lock);
	hd->audio_abort_cb = NULL;
	hd->audio_configured = false;
	hd->audio_playing = false;
	mutex_unlock(&hd->lock);

	return 0;
}