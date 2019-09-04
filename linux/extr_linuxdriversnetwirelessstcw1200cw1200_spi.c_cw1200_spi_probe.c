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
struct spi_device {int max_speed_hz; int bits_per_word; int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; int /*<<< orphan*/  chip_select; } ;
struct hwbus_priv {struct cw1200_platform_data_spi const* pdata; int /*<<< orphan*/  core; int /*<<< orphan*/  wq; int /*<<< orphan*/  lock; struct spi_device* func; } ;
struct cw1200_platform_data_spi {int spi_bits_per_word; int /*<<< orphan*/  have_5ghz; int /*<<< orphan*/  sdd_file; int /*<<< orphan*/  macaddr; int /*<<< orphan*/  ref_clk; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SPI_MODE_0 ; 
 int cw1200_core_probe (int /*<<< orphan*/ *,struct hwbus_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cw1200_spi_hwbus_ops ; 
 int cw1200_spi_irq_subscribe (struct hwbus_priv*) ; 
 int /*<<< orphan*/  cw1200_spi_irq_unsubscribe (struct hwbus_priv*) ; 
 int /*<<< orphan*/  cw1200_spi_off (struct cw1200_platform_data_spi const*) ; 
 scalar_t__ cw1200_spi_on (struct cw1200_platform_data_spi const*) ; 
 struct cw1200_platform_data_spi* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct hwbus_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct hwbus_priv*) ; 
 scalar_t__ spi_setup (struct spi_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cw1200_spi_probe(struct spi_device *func)
{
	const struct cw1200_platform_data_spi *plat_data =
		dev_get_platdata(&func->dev);
	struct hwbus_priv *self;
	int status;

	/* Sanity check speed */
	if (func->max_speed_hz > 52000000)
		func->max_speed_hz = 52000000;
	if (func->max_speed_hz < 1000000)
		func->max_speed_hz = 1000000;

	/* Fix up transfer size */
	if (plat_data->spi_bits_per_word)
		func->bits_per_word = plat_data->spi_bits_per_word;
	if (!func->bits_per_word)
		func->bits_per_word = 16;

	/* And finally.. */
	func->mode = SPI_MODE_0;

	pr_info("cw1200_wlan_spi: Probe called (CS %d M %d BPW %d CLK %d)\n",
		func->chip_select, func->mode, func->bits_per_word,
		func->max_speed_hz);

	if (cw1200_spi_on(plat_data)) {
		pr_err("spi_on() failed!\n");
		return -1;
	}

	if (spi_setup(func)) {
		pr_err("spi_setup() failed!\n");
		return -1;
	}

	self = devm_kzalloc(&func->dev, sizeof(*self), GFP_KERNEL);
	if (!self) {
		pr_err("Can't allocate SPI hwbus_priv.");
		return -ENOMEM;
	}

	self->pdata = plat_data;
	self->func = func;
	spin_lock_init(&self->lock);

	spi_set_drvdata(func, self);

	init_waitqueue_head(&self->wq);

	status = cw1200_spi_irq_subscribe(self);

	status = cw1200_core_probe(&cw1200_spi_hwbus_ops,
				   self, &func->dev, &self->core,
				   self->pdata->ref_clk,
				   self->pdata->macaddr,
				   self->pdata->sdd_file,
				   self->pdata->have_5ghz);

	if (status) {
		cw1200_spi_irq_unsubscribe(self);
		cw1200_spi_off(plat_data);
	}

	return status;
}