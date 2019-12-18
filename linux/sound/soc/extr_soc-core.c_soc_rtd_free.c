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
struct snd_soc_pcm_runtime {scalar_t__ dev_registered; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void soc_rtd_free(struct snd_soc_pcm_runtime *rtd)
{
	if (rtd->dev_registered) {
		/* we don't need to call kfree() for rtd->dev */
		device_unregister(rtd->dev);
		rtd->dev_registered = 0;
	}
}