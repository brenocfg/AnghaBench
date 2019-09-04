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
struct dw_spi {TYPE_1__* master; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int spi_controller_resume (TYPE_1__*) ; 
 int /*<<< orphan*/  spi_hw_init (int /*<<< orphan*/ *,struct dw_spi*) ; 

int dw_spi_resume_host(struct dw_spi *dws)
{
	int ret;

	spi_hw_init(&dws->master->dev, dws);
	ret = spi_controller_resume(dws->master);
	if (ret)
		dev_err(&dws->master->dev, "fail to start queue (%d)\n", ret);
	return ret;
}