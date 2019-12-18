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
struct resource {scalar_t__ start; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct hi6210_i2s {int /*<<< orphan*/  dai; int /*<<< orphan*/  clocks; void** clk; void* sysctrl; scalar_t__ base_phys; void* base; int /*<<< orphan*/  lock; struct device* dev; } ;
struct device_node {int dummy; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 size_t CLK_DACODEC ; 
 size_t CLK_I2S_BASE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 scalar_t__ IS_ERR_OR_NULL (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct hi6210_i2s*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct hi6210_i2s* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_dmaengine_pcm_register (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hi6210_i2s_dai_init ; 
 int /*<<< orphan*/  hi6210_i2s_i2s_comp ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 void* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int hi6210_i2s_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct device *dev = &pdev->dev;
	struct hi6210_i2s *i2s;
	struct resource *res;
	int ret;

	i2s = devm_kzalloc(&pdev->dev, sizeof(*i2s), GFP_KERNEL);
	if (!i2s)
		return -ENOMEM;

	i2s->dev = dev;
	spin_lock_init(&i2s->lock);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	i2s->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(i2s->base))
		return PTR_ERR(i2s->base);

	i2s->base_phys = (phys_addr_t)res->start;
	i2s->dai = hi6210_i2s_dai_init;

	dev_set_drvdata(&pdev->dev, i2s);

	i2s->sysctrl = syscon_regmap_lookup_by_phandle(node,
						"hisilicon,sysctrl-syscon");
	if (IS_ERR(i2s->sysctrl))
		return PTR_ERR(i2s->sysctrl);

	i2s->clk[CLK_DACODEC] = devm_clk_get(&pdev->dev, "dacodec");
	if (IS_ERR_OR_NULL(i2s->clk[CLK_DACODEC]))
		return PTR_ERR(i2s->clk[CLK_DACODEC]);
	i2s->clocks++;

	i2s->clk[CLK_I2S_BASE] = devm_clk_get(&pdev->dev, "i2s-base");
	if (IS_ERR_OR_NULL(i2s->clk[CLK_I2S_BASE]))
		return PTR_ERR(i2s->clk[CLK_I2S_BASE]);
	i2s->clocks++;

	ret = devm_snd_dmaengine_pcm_register(&pdev->dev, NULL, 0);
	if (ret)
		return ret;

	ret = devm_snd_soc_register_component(&pdev->dev, &hi6210_i2s_i2s_comp,
					 &i2s->dai, 1);
	return ret;
}