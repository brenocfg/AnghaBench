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
struct tse850_priv {int add_cache; int loop1_cache; int loop2_cache; void* ana; void* loop2; void* loop1; void* add; } ;
struct snd_soc_card {struct device* dev; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct tse850_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get (struct device*,char*) ; 
 int /*<<< orphan*/  regulator_disable (void*) ; 
 int regulator_enable (void*) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct tse850_priv*) ; 
 int snd_soc_register_card (struct snd_soc_card*) ; 
 struct snd_soc_card tse850_card ; 
 int tse850_dt_init (struct platform_device*) ; 

__attribute__((used)) static int tse850_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &tse850_card;
	struct device *dev = card->dev = &pdev->dev;
	struct tse850_priv *tse850;
	int ret;

	tse850 = devm_kzalloc(dev, sizeof(*tse850), GFP_KERNEL);
	if (!tse850)
		return -ENOMEM;

	snd_soc_card_set_drvdata(card, tse850);

	ret = tse850_dt_init(pdev);
	if (ret) {
		dev_err(dev, "failed to init dt info\n");
		return ret;
	}

	tse850->add = devm_gpiod_get(dev, "axentia,add", GPIOD_OUT_HIGH);
	if (IS_ERR(tse850->add)) {
		if (PTR_ERR(tse850->add) != -EPROBE_DEFER)
			dev_err(dev, "failed to get 'add' gpio\n");
		return PTR_ERR(tse850->add);
	}
	tse850->add_cache = 1;

	tse850->loop1 = devm_gpiod_get(dev, "axentia,loop1", GPIOD_OUT_HIGH);
	if (IS_ERR(tse850->loop1)) {
		if (PTR_ERR(tse850->loop1) != -EPROBE_DEFER)
			dev_err(dev, "failed to get 'loop1' gpio\n");
		return PTR_ERR(tse850->loop1);
	}
	tse850->loop1_cache = 1;

	tse850->loop2 = devm_gpiod_get(dev, "axentia,loop2", GPIOD_OUT_HIGH);
	if (IS_ERR(tse850->loop2)) {
		if (PTR_ERR(tse850->loop2) != -EPROBE_DEFER)
			dev_err(dev, "failed to get 'loop2' gpio\n");
		return PTR_ERR(tse850->loop2);
	}
	tse850->loop2_cache = 1;

	tse850->ana = devm_regulator_get(dev, "axentia,ana");
	if (IS_ERR(tse850->ana)) {
		if (PTR_ERR(tse850->ana) != -EPROBE_DEFER)
			dev_err(dev, "failed to get 'ana' regulator\n");
		return PTR_ERR(tse850->ana);
	}

	ret = regulator_enable(tse850->ana);
	if (ret < 0) {
		dev_err(dev, "failed to enable the 'ana' regulator\n");
		return ret;
	}

	ret = snd_soc_register_card(card);
	if (ret) {
		dev_err(dev, "snd_soc_register_card failed\n");
		goto err_disable_ana;
	}

	return 0;

err_disable_ana:
	regulator_disable(tse850->ana);
	return ret;
}