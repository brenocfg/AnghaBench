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
struct platform_device {int dummy; } ;
struct hdmi_audio_data {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 struct hdmi_audio_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snd_soc_unregister_card (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_hdmi_audio_remove(struct platform_device *pdev)
{
	struct hdmi_audio_data *ad = platform_get_drvdata(pdev);

	snd_soc_unregister_card(ad->card);
	return 0;
}