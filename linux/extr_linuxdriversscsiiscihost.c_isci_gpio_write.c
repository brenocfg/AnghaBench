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
struct sas_ha_struct {struct isci_host* lldd_ha; } ;
struct isci_host {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SAS_GPIO_REG_TX_GP 128 
 int sci_write_gpio_tx_gp (struct isci_host*,int,int,int*) ; 

int isci_gpio_write(struct sas_ha_struct *sas_ha, u8 reg_type, u8 reg_index,
		    u8 reg_count, u8 *write_data)
{
	struct isci_host *ihost = sas_ha->lldd_ha;
	int written;

	switch (reg_type) {
	case SAS_GPIO_REG_TX_GP:
		written = sci_write_gpio_tx_gp(ihost, reg_index, reg_count, write_data);
		break;
	default:
		written = -EINVAL;
	}

	return written;
}