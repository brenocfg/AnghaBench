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
typedef  int u32 ;
struct driver_data {scalar_t__ ssp_type; } ;

/* Variables and functions */
 scalar_t__ CE4100_SSP ; 
 scalar_t__ QUARK_X1000_SSP ; 
 int /*<<< orphan*/  SSSR ; 
 int SSSR_ALT_FRM_MASK ; 
 int pxa2xx_spi_read (struct driver_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa2xx_spi_write (struct driver_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void write_SSSR_CS(struct driver_data *drv_data, u32 val)
{
	if (drv_data->ssp_type == CE4100_SSP ||
	    drv_data->ssp_type == QUARK_X1000_SSP)
		val |= pxa2xx_spi_read(drv_data, SSSR) & SSSR_ALT_FRM_MASK;

	pxa2xx_spi_write(drv_data, SSSR, val);
}