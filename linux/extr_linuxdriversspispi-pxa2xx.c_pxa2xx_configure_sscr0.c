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
typedef  int u8 ;
typedef  int u32 ;
struct driver_data {int ssp_type; } ;

/* Variables and functions */
 int QUARK_X1000_SSCR0_DataSize (int) ; 
 int QUARK_X1000_SSCR0_Motorola ; 
#define  QUARK_X1000_SSP 128 
 int SSCR0_DataSize (int) ; 
 int SSCR0_EDSS ; 
 int SSCR0_Motorola ; 
 int SSCR0_SSE ; 

__attribute__((used)) static u32 pxa2xx_configure_sscr0(const struct driver_data *drv_data,
				  u32 clk_div, u8 bits)
{
	switch (drv_data->ssp_type) {
	case QUARK_X1000_SSP:
		return clk_div
			| QUARK_X1000_SSCR0_Motorola
			| QUARK_X1000_SSCR0_DataSize(bits > 32 ? 8 : bits)
			| SSCR0_SSE;
	default:
		return clk_div
			| SSCR0_Motorola
			| SSCR0_DataSize(bits > 16 ? bits - 16 : bits)
			| SSCR0_SSE
			| (bits > 16 ? SSCR0_EDSS : 0);
	}
}