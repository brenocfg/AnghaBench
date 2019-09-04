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
struct driver_data {int int_cr1; TYPE_1__* pdev; int /*<<< orphan*/  clear_sr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSCR0 ; 
 int SSCR0_SSE ; 
 int /*<<< orphan*/  SSCR1 ; 
 int /*<<< orphan*/  SSTO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pxa25x_ssp_comp (struct driver_data*) ; 
 int pxa2xx_spi_read (struct driver_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa2xx_spi_write (struct driver_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_SSSR_CS (struct driver_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_bad_msg(struct driver_data *drv_data)
{
	pxa2xx_spi_write(drv_data, SSCR0,
			 pxa2xx_spi_read(drv_data, SSCR0) & ~SSCR0_SSE);
	pxa2xx_spi_write(drv_data, SSCR1,
			 pxa2xx_spi_read(drv_data, SSCR1) & ~drv_data->int_cr1);
	if (!pxa25x_ssp_comp(drv_data))
		pxa2xx_spi_write(drv_data, SSTO, 0);
	write_SSSR_CS(drv_data, drv_data->clear_sr);

	dev_err(&drv_data->pdev->dev,
		"bad message state in interrupt handler\n");
}