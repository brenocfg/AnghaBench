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
struct driver_data {int ssp_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE4100_SSCR1_CHANGE_MASK ; 
#define  CE4100_SSP 129 
 int /*<<< orphan*/  QUARK_X1000_SSCR1_CHANGE_MASK ; 
#define  QUARK_X1000_SSP 128 
 int /*<<< orphan*/  SSCR1_CHANGE_MASK ; 

__attribute__((used)) static u32 pxa2xx_spi_get_ssrc1_change_mask(const struct driver_data *drv_data)
{
	switch (drv_data->ssp_type) {
	case QUARK_X1000_SSP:
		return QUARK_X1000_SSCR1_CHANGE_MASK;
	case CE4100_SSP:
		return CE4100_SSCR1_CHANGE_MASK;
	default:
		return SSCR1_CHANGE_MASK;
	}
}