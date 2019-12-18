#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct resource {scalar_t__ start; } ;
struct TYPE_5__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  pcm_free; int /*<<< orphan*/  pcm_new; int /*<<< orphan*/ * ops; int /*<<< orphan*/  name; } ;
struct dma_object {int ssi_fifo_depth; int /*<<< orphan*/  irq; int /*<<< orphan*/  channel; TYPE_2__ dai; scalar_t__ ssi_srx_phys; scalar_t__ ssi_stx_phys; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ REG_SSI_SRX0 ; 
 scalar_t__ REG_SSI_STX0 ; 
 int be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct dma_object*) ; 
 int devm_snd_soc_register_component (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct device_node* find_ssi_node (struct device_node*) ; 
 int /*<<< orphan*/  fsl_dma_free_dma_buffers ; 
 int /*<<< orphan*/  fsl_dma_new ; 
 int /*<<< orphan*/  fsl_dma_ops ; 
 int /*<<< orphan*/  irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dma_object*) ; 
 struct dma_object* kzalloc (int,int /*<<< orphan*/ ) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int fsl_soc_dma_probe(struct platform_device *pdev)
{
	struct dma_object *dma;
	struct device_node *np = pdev->dev.of_node;
	struct device_node *ssi_np;
	struct resource res;
	const uint32_t *iprop;
	int ret;

	/* Find the SSI node that points to us. */
	ssi_np = find_ssi_node(np);
	if (!ssi_np) {
		dev_err(&pdev->dev, "cannot find parent SSI node\n");
		return -ENODEV;
	}

	ret = of_address_to_resource(ssi_np, 0, &res);
	if (ret) {
		dev_err(&pdev->dev, "could not determine resources for %pOF\n",
			ssi_np);
		of_node_put(ssi_np);
		return ret;
	}

	dma = kzalloc(sizeof(*dma), GFP_KERNEL);
	if (!dma) {
		of_node_put(ssi_np);
		return -ENOMEM;
	}

	dma->dai.name = DRV_NAME;
	dma->dai.ops = &fsl_dma_ops;
	dma->dai.pcm_new = fsl_dma_new;
	dma->dai.pcm_free = fsl_dma_free_dma_buffers;

	/* Store the SSI-specific information that we need */
	dma->ssi_stx_phys = res.start + REG_SSI_STX0;
	dma->ssi_srx_phys = res.start + REG_SSI_SRX0;

	iprop = of_get_property(ssi_np, "fsl,fifo-depth", NULL);
	if (iprop)
		dma->ssi_fifo_depth = be32_to_cpup(iprop);
	else
                /* Older 8610 DTs didn't have the fifo-depth property */
		dma->ssi_fifo_depth = 8;

	of_node_put(ssi_np);

	ret = devm_snd_soc_register_component(&pdev->dev, &dma->dai, NULL, 0);
	if (ret) {
		dev_err(&pdev->dev, "could not register platform\n");
		kfree(dma);
		return ret;
	}

	dma->channel = of_iomap(np, 0);
	dma->irq = irq_of_parse_and_map(np, 0);

	dev_set_drvdata(&pdev->dev, dma);

	return 0;
}