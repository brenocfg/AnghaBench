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
typedef  int /*<<< orphan*/  u32 ;
struct spi_device {int /*<<< orphan*/  controller; } ;
struct lpss_config {int /*<<< orphan*/  reg_cs_ctrl; } ;
struct driver_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPSS_CS_CONTROL_CS_HIGH ; 
 int /*<<< orphan*/  __lpss_ssp_read_priv (struct driver_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lpss_ssp_write_priv (struct driver_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lpss_config* lpss_get_config (struct driver_data*) ; 
 int /*<<< orphan*/  lpss_ssp_select_cs (struct spi_device*,struct lpss_config const*) ; 
 struct driver_data* spi_controller_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpss_ssp_cs_control(struct spi_device *spi, bool enable)
{
	struct driver_data *drv_data =
		spi_controller_get_devdata(spi->controller);
	const struct lpss_config *config;
	u32 value;

	config = lpss_get_config(drv_data);

	if (enable)
		lpss_ssp_select_cs(spi, config);

	value = __lpss_ssp_read_priv(drv_data, config->reg_cs_ctrl);
	if (enable)
		value &= ~LPSS_CS_CONTROL_CS_HIGH;
	else
		value |= LPSS_CS_CONTROL_CS_HIGH;
	__lpss_ssp_write_priv(drv_data, config->reg_cs_ctrl, value);
}