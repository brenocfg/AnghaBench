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
struct xlgmac_pdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xlgmac_config_rx_flow_control (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  xlgmac_config_tx_flow_control (struct xlgmac_pdata*) ; 

__attribute__((used)) static void xlgmac_config_flow_control(struct xlgmac_pdata *pdata)
{
	xlgmac_config_tx_flow_control(pdata);
	xlgmac_config_rx_flow_control(pdata);
}