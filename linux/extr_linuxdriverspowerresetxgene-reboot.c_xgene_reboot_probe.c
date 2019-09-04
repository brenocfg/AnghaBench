#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int priority; int /*<<< orphan*/  notifier_call; } ;
struct xgene_reboot_context {int mask; int /*<<< orphan*/  csr; TYPE_1__ restart_handler; struct device* dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct xgene_reboot_context* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_iomap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int register_restart_handler (TYPE_1__*) ; 
 int /*<<< orphan*/  xgene_restart_handler ; 

__attribute__((used)) static int xgene_reboot_probe(struct platform_device *pdev)
{
	struct xgene_reboot_context *ctx;
	struct device *dev = &pdev->dev;
	int err;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->csr = of_iomap(dev->of_node, 0);
	if (!ctx->csr) {
		dev_err(dev, "can not map resource\n");
		return -ENODEV;
	}

	if (of_property_read_u32(dev->of_node, "mask", &ctx->mask))
		ctx->mask = 0xFFFFFFFF;

	ctx->dev = dev;
	ctx->restart_handler.notifier_call = xgene_restart_handler;
	ctx->restart_handler.priority = 128;
	err = register_restart_handler(&ctx->restart_handler);
	if (err) {
		iounmap(ctx->csr);
		dev_err(dev, "cannot register restart handler (err=%d)\n", err);
	}

	return err;
}