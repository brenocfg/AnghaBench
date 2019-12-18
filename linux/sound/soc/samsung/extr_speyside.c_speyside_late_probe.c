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
struct snd_soc_card {int /*<<< orphan*/  dapm; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_soc_dapm_ignore_suspend (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int speyside_late_probe(struct snd_soc_card *card)
{
	snd_soc_dapm_ignore_suspend(&card->dapm, "Headphone");
	snd_soc_dapm_ignore_suspend(&card->dapm, "Headset Mic");
	snd_soc_dapm_ignore_suspend(&card->dapm, "Main AMIC");
	snd_soc_dapm_ignore_suspend(&card->dapm, "Main DMIC");
	snd_soc_dapm_ignore_suspend(&card->dapm, "Main Speaker");
	snd_soc_dapm_ignore_suspend(&card->dapm, "WM1250 Output");
	snd_soc_dapm_ignore_suspend(&card->dapm, "WM1250 Input");

	return 0;
}