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
struct ScsiReqBlk {int dummy; } ;
struct DeviceCtlBlk {int dummy; } ;
struct AdapterCtlBlk {unsigned long io_port_base; unsigned int irq_level; int /*<<< orphan*/  io_port_len; int /*<<< orphan*/  srb_array; int /*<<< orphan*/  dcb_map; int /*<<< orphan*/  scsi_host; int /*<<< orphan*/  eeprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_0 ; 
 int /*<<< orphan*/  DC395X_NAME ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  adapter_init_chip (struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  adapter_init_params (struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  adapter_init_scsi_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adapter_print_config (struct AdapterCtlBlk*) ; 
 scalar_t__ adapter_sg_tables_alloc (struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  adapter_sg_tables_free (struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  check_eeprom (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  dc395x_interrupt ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,struct AdapterCtlBlk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_irq (int,struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  print_eeprom_settings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_region (long,int /*<<< orphan*/ ) ; 
 scalar_t__ request_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  request_region (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_basic_config (struct AdapterCtlBlk*) ; 

__attribute__((used)) static int adapter_init(struct AdapterCtlBlk *acb, unsigned long io_port,
			u32 io_port_len, unsigned int irq)
{
	if (!request_region(io_port, io_port_len, DC395X_NAME)) {
		dprintkl(KERN_ERR, "Failed to reserve IO region 0x%lx\n", io_port);
		goto failed;
	}
	/* store port base to indicate we have registered it */
	acb->io_port_base = io_port;
	acb->io_port_len = io_port_len;
	
	if (request_irq(irq, dc395x_interrupt, IRQF_SHARED, DC395X_NAME, acb)) {
	    	/* release the region we just claimed */
		dprintkl(KERN_INFO, "Failed to register IRQ\n");
		goto failed;
	}
	/* store irq to indicate we have registered it */
	acb->irq_level = irq;

	/* get eeprom configuration information and command line settings etc */
	check_eeprom(&acb->eeprom, io_port);
 	print_eeprom_settings(&acb->eeprom);

	/* setup adapter control block */	
	adapter_init_params(acb);
	
	/* display card connectors/termination settings */
 	adapter_print_config(acb);

	if (adapter_sg_tables_alloc(acb)) {
		dprintkl(KERN_DEBUG, "Memory allocation for SG tables failed\n");
		goto failed;
	}
	adapter_init_scsi_host(acb->scsi_host);
	adapter_init_chip(acb);
	set_basic_config(acb);

	dprintkdbg(DBG_0,
		"adapter_init: acb=%p, pdcb_map=%p psrb_array=%p "
		"size{acb=0x%04x dcb=0x%04x srb=0x%04x}\n",
		acb, acb->dcb_map, acb->srb_array, sizeof(struct AdapterCtlBlk),
		sizeof(struct DeviceCtlBlk), sizeof(struct ScsiReqBlk));
	return 0;

failed:
	if (acb->irq_level)
		free_irq(acb->irq_level, acb);
	if (acb->io_port_base)
		release_region(acb->io_port_base, acb->io_port_len);
	adapter_sg_tables_free(acb);

	return 1;
}