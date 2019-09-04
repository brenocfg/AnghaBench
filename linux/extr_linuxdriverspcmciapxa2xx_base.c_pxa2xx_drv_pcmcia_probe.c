#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct soc_pcmcia_socket {struct clk* clk; scalar_t__ nr; } ;
struct skt_dev_info {int nskt; struct soc_pcmcia_socket* skt; } ;
struct TYPE_7__ {scalar_t__ platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct pcmcia_low_level {int nr; scalar_t__ first; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  SKT_DEV_INFO_SIZE (int) ; 
 scalar_t__ cpu_is_pxa320 () ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct skt_dev_info*) ; 
 struct clk* devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct skt_dev_info* devm_kzalloc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa2xx_configure_sockets (TYPE_1__*,struct pcmcia_low_level*) ; 
 int pxa2xx_drv_pcmcia_add_one (struct soc_pcmcia_socket*) ; 
 int /*<<< orphan*/  pxa2xx_drv_pcmcia_ops (struct pcmcia_low_level*) ; 
 int /*<<< orphan*/  soc_pcmcia_init_one (struct soc_pcmcia_socket*,struct pcmcia_low_level*,TYPE_1__*) ; 
 int /*<<< orphan*/  soc_pcmcia_remove_one (struct soc_pcmcia_socket*) ; 

__attribute__((used)) static int pxa2xx_drv_pcmcia_probe(struct platform_device *dev)
{
	int i, ret = 0;
	struct pcmcia_low_level *ops;
	struct skt_dev_info *sinfo;
	struct soc_pcmcia_socket *skt;
	struct clk *clk;

	ops = (struct pcmcia_low_level *)dev->dev.platform_data;
	if (!ops) {
		ret = -ENODEV;
		goto err0;
	}

	if (cpu_is_pxa320() && ops->nr > 1) {
		dev_err(&dev->dev, "pxa320 supports only one pcmcia slot");
		ret = -EINVAL;
		goto err0;
	}

	clk = devm_clk_get(&dev->dev, NULL);
	if (IS_ERR(clk))
		return -ENODEV;

	pxa2xx_drv_pcmcia_ops(ops);

	sinfo = devm_kzalloc(&dev->dev, SKT_DEV_INFO_SIZE(ops->nr),
			     GFP_KERNEL);
	if (!sinfo)
		return -ENOMEM;

	sinfo->nskt = ops->nr;

	/* Initialize processor specific parameters */
	for (i = 0; i < ops->nr; i++) {
		skt = &sinfo->skt[i];

		skt->nr = ops->first + i;
		skt->clk = clk;
		soc_pcmcia_init_one(skt, ops, &dev->dev);

		ret = pxa2xx_drv_pcmcia_add_one(skt);
		if (ret)
			goto err1;
	}

	pxa2xx_configure_sockets(&dev->dev, ops);
	dev_set_drvdata(&dev->dev, sinfo);

	return 0;

err1:
	while (--i >= 0)
		soc_pcmcia_remove_one(&sinfo->skt[i]);

err0:
	return ret;
}