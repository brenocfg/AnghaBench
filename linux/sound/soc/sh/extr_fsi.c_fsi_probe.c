#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct sh_fsi_platform_info {int /*<<< orphan*/  port_b; int /*<<< orphan*/  port_a; } ;
struct resource {scalar_t__ start; } ;
struct platform_device_id {scalar_t__ driver_data; } ;
struct TYPE_13__ {int /*<<< orphan*/  platform_data; struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; struct platform_device_id* id_entry; } ;
struct fsi_priv {struct fsi_master* master; scalar_t__ phys; scalar_t__ base; } ;
struct fsi_master {struct fsi_priv fsia; struct fsi_priv fsib; scalar_t__ base; int /*<<< orphan*/  lock; struct fsi_core const* core; } ;
struct fsi_core {int dummy; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct fsi_master*) ; 
 scalar_t__ devm_ioremap_nocache (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct fsi_master* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fsi_master*) ; 
 int devm_snd_soc_register_component (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsi_handler_init (struct fsi_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsi_interrupt ; 
 int /*<<< orphan*/  fsi_of_parse (char*,struct device_node*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fsi_port_info_init (struct fsi_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsi_soc_component ; 
 int /*<<< orphan*/  fsi_soc_dai ; 
 int fsi_stream_probe (struct fsi_priv*,TYPE_1__*) ; 
 int /*<<< orphan*/  fsi_stream_remove (struct fsi_priv*) ; 
 int /*<<< orphan*/  memcpy (struct sh_fsi_platform_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct sh_fsi_platform_info*,int /*<<< orphan*/ ,int) ; 
 struct fsi_core* of_device_get_match_data (TYPE_1__*) ; 
 unsigned int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsi_probe(struct platform_device *pdev)
{
	struct fsi_master *master;
	struct device_node *np = pdev->dev.of_node;
	struct sh_fsi_platform_info info;
	const struct fsi_core *core;
	struct fsi_priv *fsi;
	struct resource *res;
	unsigned int irq;
	int ret;

	memset(&info, 0, sizeof(info));

	core = NULL;
	if (np) {
		core = of_device_get_match_data(&pdev->dev);
		fsi_of_parse("fsia", np, &info.port_a, &pdev->dev);
		fsi_of_parse("fsib", np, &info.port_b, &pdev->dev);
	} else {
		const struct platform_device_id	*id_entry = pdev->id_entry;
		if (id_entry)
			core = (struct fsi_core *)id_entry->driver_data;

		if (pdev->dev.platform_data)
			memcpy(&info, pdev->dev.platform_data, sizeof(info));
	}

	if (!core) {
		dev_err(&pdev->dev, "unknown fsi device\n");
		return -ENODEV;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	irq = platform_get_irq(pdev, 0);
	if (!res || (int)irq <= 0) {
		dev_err(&pdev->dev, "Not enough FSI platform resources.\n");
		return -ENODEV;
	}

	master = devm_kzalloc(&pdev->dev, sizeof(*master), GFP_KERNEL);
	if (!master)
		return -ENOMEM;

	master->base = devm_ioremap_nocache(&pdev->dev,
					    res->start, resource_size(res));
	if (!master->base) {
		dev_err(&pdev->dev, "Unable to ioremap FSI registers.\n");
		return -ENXIO;
	}

	/* master setting */
	master->core		= core;
	spin_lock_init(&master->lock);

	/* FSI A setting */
	fsi		= &master->fsia;
	fsi->base	= master->base;
	fsi->phys	= res->start;
	fsi->master	= master;
	fsi_port_info_init(fsi, &info.port_a);
	fsi_handler_init(fsi, &info.port_a);
	ret = fsi_stream_probe(fsi, &pdev->dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "FSIA stream probe failed\n");
		return ret;
	}

	/* FSI B setting */
	fsi		= &master->fsib;
	fsi->base	= master->base + 0x40;
	fsi->phys	= res->start + 0x40;
	fsi->master	= master;
	fsi_port_info_init(fsi, &info.port_b);
	fsi_handler_init(fsi, &info.port_b);
	ret = fsi_stream_probe(fsi, &pdev->dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "FSIB stream probe failed\n");
		goto exit_fsia;
	}

	pm_runtime_enable(&pdev->dev);
	dev_set_drvdata(&pdev->dev, master);

	ret = devm_request_irq(&pdev->dev, irq, &fsi_interrupt, 0,
			       dev_name(&pdev->dev), master);
	if (ret) {
		dev_err(&pdev->dev, "irq request err\n");
		goto exit_fsib;
	}

	ret = devm_snd_soc_register_component(&pdev->dev, &fsi_soc_component,
				    fsi_soc_dai, ARRAY_SIZE(fsi_soc_dai));
	if (ret < 0) {
		dev_err(&pdev->dev, "cannot snd component register\n");
		goto exit_fsib;
	}

	return ret;

exit_fsib:
	pm_runtime_disable(&pdev->dev);
	fsi_stream_remove(&master->fsib);
exit_fsia:
	fsi_stream_remove(&master->fsia);

	return ret;
}