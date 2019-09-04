#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct device {int dummy; } ;
struct fsl_mc_device {int /*<<< orphan*/  mc_io; int /*<<< orphan*/  mc_handle; TYPE_2__* regions; TYPE_1__ obj_desc; struct device dev; } ;
struct dpio_priv {int /*<<< orphan*/  io; } ;
struct dpio_attr {int num_priorities; int /*<<< orphan*/  qbman_version; } ;
struct dpaa2_io_desc {int receives_notifications; int has_8prio; int cpu; int /*<<< orphan*/  regs_cinh; int /*<<< orphan*/  regs_cena; int /*<<< orphan*/  dpio_id; int /*<<< orphan*/  qman_version; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int ERANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMREMAP_WC ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpu_possible (int) ; 
 int cpumask_first (int /*<<< orphan*/ ) ; 
 int cpumask_next (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct dpio_priv*) ; 
 int /*<<< orphan*/  devm_ioremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dpio_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_memremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_io_create (struct dpaa2_io_desc*) ; 
 int /*<<< orphan*/  dpio_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpio_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dpio_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dpio_get_attributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpio_attr*) ; 
 int dpio_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int fsl_mc_allocate_irqs (struct fsl_mc_device*) ; 
 int /*<<< orphan*/  fsl_mc_free_irqs (struct fsl_mc_device*) ; 
 int fsl_mc_portal_allocate (struct fsl_mc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_mc_portal_free (int /*<<< orphan*/ ) ; 
 int register_dpio_irq_handlers (struct fsl_mc_device*,int) ; 
 int /*<<< orphan*/  resource_size (TYPE_2__*) ; 
 int /*<<< orphan*/  unregister_dpio_irq_handlers (struct fsl_mc_device*) ; 

__attribute__((used)) static int dpaa2_dpio_probe(struct fsl_mc_device *dpio_dev)
{
	struct dpio_attr dpio_attrs;
	struct dpaa2_io_desc desc;
	struct dpio_priv *priv;
	int err = -ENOMEM;
	struct device *dev = &dpio_dev->dev;
	static int next_cpu = -1;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		goto err_priv_alloc;

	dev_set_drvdata(dev, priv);

	err = fsl_mc_portal_allocate(dpio_dev, 0, &dpio_dev->mc_io);
	if (err) {
		dev_dbg(dev, "MC portal allocation failed\n");
		err = -EPROBE_DEFER;
		goto err_priv_alloc;
	}

	err = dpio_open(dpio_dev->mc_io, 0, dpio_dev->obj_desc.id,
			&dpio_dev->mc_handle);
	if (err) {
		dev_err(dev, "dpio_open() failed\n");
		goto err_open;
	}

	err = dpio_get_attributes(dpio_dev->mc_io, 0, dpio_dev->mc_handle,
				  &dpio_attrs);
	if (err) {
		dev_err(dev, "dpio_get_attributes() failed %d\n", err);
		goto err_get_attr;
	}
	desc.qman_version = dpio_attrs.qbman_version;

	err = dpio_enable(dpio_dev->mc_io, 0, dpio_dev->mc_handle);
	if (err) {
		dev_err(dev, "dpio_enable() failed %d\n", err);
		goto err_get_attr;
	}

	/* initialize DPIO descriptor */
	desc.receives_notifications = dpio_attrs.num_priorities ? 1 : 0;
	desc.has_8prio = dpio_attrs.num_priorities == 8 ? 1 : 0;
	desc.dpio_id = dpio_dev->obj_desc.id;

	/* get the cpu to use for the affinity hint */
	if (next_cpu == -1)
		next_cpu = cpumask_first(cpu_online_mask);
	else
		next_cpu = cpumask_next(next_cpu, cpu_online_mask);

	if (!cpu_possible(next_cpu)) {
		dev_err(dev, "probe failed. Number of DPIOs exceeds NR_CPUS.\n");
		err = -ERANGE;
		goto err_allocate_irqs;
	}
	desc.cpu = next_cpu;

	/*
	 * Set the CENA regs to be the cache inhibited area of the portal to
	 * avoid coherency issues if a user migrates to another core.
	 */
	desc.regs_cena = devm_memremap(dev, dpio_dev->regions[1].start,
				       resource_size(&dpio_dev->regions[1]),
				       MEMREMAP_WC);
	if (IS_ERR(desc.regs_cena)) {
		dev_err(dev, "devm_memremap failed\n");
		err = PTR_ERR(desc.regs_cena);
		goto err_allocate_irqs;
	}

	desc.regs_cinh = devm_ioremap(dev, dpio_dev->regions[1].start,
				      resource_size(&dpio_dev->regions[1]));
	if (!desc.regs_cinh) {
		err = -ENOMEM;
		dev_err(dev, "devm_ioremap failed\n");
		goto err_allocate_irqs;
	}

	err = fsl_mc_allocate_irqs(dpio_dev);
	if (err) {
		dev_err(dev, "fsl_mc_allocate_irqs failed. err=%d\n", err);
		goto err_allocate_irqs;
	}

	err = register_dpio_irq_handlers(dpio_dev, desc.cpu);
	if (err)
		goto err_register_dpio_irq;

	priv->io = dpaa2_io_create(&desc);
	if (!priv->io) {
		dev_err(dev, "dpaa2_io_create failed\n");
		err = -ENOMEM;
		goto err_dpaa2_io_create;
	}

	dev_info(dev, "probed\n");
	dev_dbg(dev, "   receives_notifications = %d\n",
		desc.receives_notifications);
	dpio_close(dpio_dev->mc_io, 0, dpio_dev->mc_handle);
	fsl_mc_portal_free(dpio_dev->mc_io);

	return 0;

err_dpaa2_io_create:
	unregister_dpio_irq_handlers(dpio_dev);
err_register_dpio_irq:
	fsl_mc_free_irqs(dpio_dev);
err_allocate_irqs:
	dpio_disable(dpio_dev->mc_io, 0, dpio_dev->mc_handle);
err_get_attr:
	dpio_close(dpio_dev->mc_io, 0, dpio_dev->mc_handle);
err_open:
	fsl_mc_portal_free(dpio_dev->mc_io);
err_priv_alloc:
	return err;
}