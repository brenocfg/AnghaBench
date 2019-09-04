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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct nuc900_audio {int irq_num; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; int /*<<< orphan*/  mmio; int /*<<< orphan*/  res; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nuc900_audio* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfp_set_groupg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nuc900_ac97_component ; 
 int /*<<< orphan*/  nuc900_ac97_dai ; 
 struct nuc900_audio* nuc900_ac97_data ; 
 int /*<<< orphan*/  nuc900_ac97_ops ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int snd_soc_set_ac97_ops (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nuc900_ac97_drvprobe(struct platform_device *pdev)
{
	struct nuc900_audio *nuc900_audio;
	int ret;

	if (nuc900_ac97_data)
		return -EBUSY;

	nuc900_audio = devm_kzalloc(&pdev->dev, sizeof(struct nuc900_audio),
				    GFP_KERNEL);
	if (!nuc900_audio)
		return -ENOMEM;

	spin_lock_init(&nuc900_audio->lock);

	nuc900_audio->res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	nuc900_audio->mmio = devm_ioremap_resource(&pdev->dev,
						   nuc900_audio->res);
	if (IS_ERR(nuc900_audio->mmio))
		return PTR_ERR(nuc900_audio->mmio);

	nuc900_audio->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(nuc900_audio->clk)) {
		ret = PTR_ERR(nuc900_audio->clk);
		goto out;
	}

	ret = platform_get_irq(pdev, 0);
	if (ret < 0)
		goto out;
	nuc900_audio->irq_num = ret;

	nuc900_ac97_data = nuc900_audio;

	ret = snd_soc_set_ac97_ops(&nuc900_ac97_ops);
	if (ret)
		goto out;

	ret = snd_soc_register_component(&pdev->dev, &nuc900_ac97_component,
					 &nuc900_ac97_dai, 1);
	if (ret)
		goto out;

	/* enbale ac97 multifunction pin */
	mfp_set_groupg(nuc900_audio->dev, NULL);

	return 0;

out:
	snd_soc_set_ac97_ops(NULL);
	return ret;
}