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
struct port_cell_info {int port_num; void** tx_link_rate; int /*<<< orphan*/  member_0; } ;
typedef  int DSL_uint32_t ;
typedef  int /*<<< orphan*/  DSL_DEV_MeiError_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSL_DEV_MEI_ERR_SUCCESS ; 
 int /*<<< orphan*/  IFX_MEI_EMSG (char*,...) ; 
 void** g_tx_link_rate ; 
 int /*<<< orphan*/  g_xdata_addr ; 
 int /*<<< orphan*/  ifx_mei_atm_showtime_enter (struct port_cell_info*,int /*<<< orphan*/ ) ; 

DSL_DEV_MeiError_t
DSL_BSP_Showtime (DSL_DEV_Device_t * dev, DSL_uint32_t rate_fast, DSL_uint32_t rate_intl)
{
    struct port_cell_info port_cell = {0};

	IFX_MEI_EMSG ("Datarate US intl = %d, fast = %d\n", (int)rate_intl,
			    (int)rate_fast);

    if ( rate_fast )
        g_tx_link_rate[0] = rate_fast / (53 * 8);
    if ( rate_intl )
        g_tx_link_rate[1] = rate_intl / (53 * 8);

    if ( g_tx_link_rate[0] == 0 && g_tx_link_rate[1] == 0 ) {
        IFX_MEI_EMSG ("Got rate fail.\n");
    }

	if ( ifx_mei_atm_showtime_enter )
	{
	    port_cell.port_num = 2;
	    port_cell.tx_link_rate[0] = g_tx_link_rate[0];
	    port_cell.tx_link_rate[1] = g_tx_link_rate[1];
        ifx_mei_atm_showtime_enter(&port_cell, g_xdata_addr);
	}
	else
	{
		IFX_MEI_EMSG("no hookup from ATM driver to set cell rate\n");
	}

	return DSL_DEV_MEI_ERR_SUCCESS;
}