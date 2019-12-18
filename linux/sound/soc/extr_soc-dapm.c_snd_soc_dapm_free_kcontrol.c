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
struct snd_soc_card {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static void
snd_soc_dapm_free_kcontrol(struct snd_soc_card *card,
			unsigned long *private_value,
			int num_params,
			const char **w_param_text)
{
	int count;

	devm_kfree(card->dev, (void *)*private_value);

	if (!w_param_text)
		return;

	for (count = 0 ; count < num_params; count++)
		devm_kfree(card->dev, (void *)w_param_text[count]);
	devm_kfree(card->dev, w_param_text);
}