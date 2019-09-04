#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct spi_mem_driver {int (* probe ) (struct spi_mem*) ;} ;
struct spi_mem {int /*<<< orphan*/  name; struct spi_device* spi; } ;
struct TYPE_5__ {int /*<<< orphan*/  driver; } ;
struct spi_device {TYPE_2__ dev; struct spi_controller* controller; } ;
struct spi_controller {TYPE_1__* mem_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_name ) (struct spi_mem*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 struct spi_mem* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct spi_mem*) ; 
 int /*<<< orphan*/  stub1 (struct spi_mem*) ; 
 int stub2 (struct spi_mem*) ; 
 struct spi_mem_driver* to_spi_mem_drv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spi_mem_probe(struct spi_device *spi)
{
	struct spi_mem_driver *memdrv = to_spi_mem_drv(spi->dev.driver);
	struct spi_controller *ctlr = spi->controller;
	struct spi_mem *mem;

	mem = devm_kzalloc(&spi->dev, sizeof(*mem), GFP_KERNEL);
	if (!mem)
		return -ENOMEM;

	mem->spi = spi;

	if (ctlr->mem_ops && ctlr->mem_ops->get_name)
		mem->name = ctlr->mem_ops->get_name(mem);
	else
		mem->name = dev_name(&spi->dev);

	if (IS_ERR_OR_NULL(mem->name))
		return PTR_ERR(mem->name);

	spi_set_drvdata(spi, mem);

	return memdrv->probe(mem);
}