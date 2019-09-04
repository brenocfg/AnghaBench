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
struct pcm030_audio_data {int /*<<< orphan*/  codec_device; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 struct pcm030_audio_data* platform_get_drvdata (struct platform_device*) ; 
 int snd_soc_unregister_card (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcm030_fabric_remove(struct platform_device *op)
{
	struct pcm030_audio_data *pdata = platform_get_drvdata(op);
	int ret;

	ret = snd_soc_unregister_card(pdata->card);
	platform_device_unregister(pdata->codec_device);

	return ret;
}