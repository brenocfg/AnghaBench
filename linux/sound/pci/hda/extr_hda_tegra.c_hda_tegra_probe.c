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
struct snd_card {struct azx* private_data; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct azx {int dummy; } ;
struct hda_tegra {int /*<<< orphan*/  probe_work; int /*<<< orphan*/ * dev; struct azx chip; } ;

/* Variables and functions */
 unsigned int AZX_DCAPS_CORBRP_SELF_CLEAR ; 
 unsigned int AZX_DCAPS_PM_RUNTIME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_DEFAULT_IDX1 ; 
 int /*<<< orphan*/  SNDRV_DEFAULT_STR1 ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  azx_has_pm_runtime (struct azx*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct snd_card*) ; 
 struct hda_tegra* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int hda_tegra_create (struct snd_card*,unsigned int const,struct hda_tegra*) ; 
 int hda_tegra_init_clk (struct hda_tegra*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_forbid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 
 int snd_card_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_card**) ; 

__attribute__((used)) static int hda_tegra_probe(struct platform_device *pdev)
{
	const unsigned int driver_flags = AZX_DCAPS_CORBRP_SELF_CLEAR |
					  AZX_DCAPS_PM_RUNTIME;
	struct snd_card *card;
	struct azx *chip;
	struct hda_tegra *hda;
	int err;

	hda = devm_kzalloc(&pdev->dev, sizeof(*hda), GFP_KERNEL);
	if (!hda)
		return -ENOMEM;
	hda->dev = &pdev->dev;
	chip = &hda->chip;

	err = snd_card_new(&pdev->dev, SNDRV_DEFAULT_IDX1, SNDRV_DEFAULT_STR1,
			   THIS_MODULE, 0, &card);
	if (err < 0) {
		dev_err(&pdev->dev, "Error creating card!\n");
		return err;
	}

	err = hda_tegra_init_clk(hda);
	if (err < 0)
		goto out_free;

	err = hda_tegra_create(card, driver_flags, hda);
	if (err < 0)
		goto out_free;
	card->private_data = chip;

	dev_set_drvdata(&pdev->dev, card);

	pm_runtime_enable(hda->dev);
	if (!azx_has_pm_runtime(chip))
		pm_runtime_forbid(hda->dev);

	schedule_work(&hda->probe_work);

	return 0;

out_free:
	snd_card_free(card);
	return err;
}