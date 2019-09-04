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
struct sdio_func {int num; int /*<<< orphan*/  dev; TYPE_1__* card; } ;
struct sdio_device_id {int dummy; } ;
struct hwbus_priv {TYPE_2__* pdata; int /*<<< orphan*/  core; struct sdio_func* func; } ;
struct TYPE_4__ {int /*<<< orphan*/  have_5ghz; int /*<<< orphan*/  sdd_file; int /*<<< orphan*/  macaddr; int /*<<< orphan*/  ref_clk; } ;
struct TYPE_3__ {int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MMC_QUIRK_LENIENT_FN0 ; 
 int cw1200_core_probe (int /*<<< orphan*/ *,struct hwbus_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cw1200_sdio_hwbus_ops ; 
 int cw1200_sdio_irq_subscribe (struct hwbus_priv*) ; 
 int /*<<< orphan*/  cw1200_sdio_irq_unsubscribe (struct hwbus_priv*) ; 
 TYPE_2__* global_plat_data ; 
 int /*<<< orphan*/  kfree (struct hwbus_priv*) ; 
 struct hwbus_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_disable_func (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_enable_func (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_set_drvdata (struct sdio_func*,struct hwbus_priv*) ; 

__attribute__((used)) static int cw1200_sdio_probe(struct sdio_func *func,
			     const struct sdio_device_id *id)
{
	struct hwbus_priv *self;
	int status;

	pr_info("cw1200_wlan_sdio: Probe called\n");

	/* We are only able to handle the wlan function */
	if (func->num != 0x01)
		return -ENODEV;

	self = kzalloc(sizeof(*self), GFP_KERNEL);
	if (!self) {
		pr_err("Can't allocate SDIO hwbus_priv.\n");
		return -ENOMEM;
	}

	func->card->quirks |= MMC_QUIRK_LENIENT_FN0;

	self->pdata = global_plat_data; /* FIXME */
	self->func = func;
	sdio_set_drvdata(func, self);
	sdio_claim_host(func);
	sdio_enable_func(func);
	sdio_release_host(func);

	status = cw1200_sdio_irq_subscribe(self);

	status = cw1200_core_probe(&cw1200_sdio_hwbus_ops,
				   self, &func->dev, &self->core,
				   self->pdata->ref_clk,
				   self->pdata->macaddr,
				   self->pdata->sdd_file,
				   self->pdata->have_5ghz);
	if (status) {
		cw1200_sdio_irq_unsubscribe(self);
		sdio_claim_host(func);
		sdio_disable_func(func);
		sdio_release_host(func);
		sdio_set_drvdata(func, NULL);
		kfree(self);
	}

	return status;
}