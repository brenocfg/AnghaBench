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
struct asd_sas_port {int /*<<< orphan*/  num_phys; int /*<<< orphan*/  id; int /*<<< orphan*/  oob_mode; int /*<<< orphan*/  tproto; int /*<<< orphan*/  iproto; int /*<<< orphan*/  attached_sas_addr; int /*<<< orphan*/  sas_addr; int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAS_DPRINTK (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sas_dump_port(struct asd_sas_port *port)
{
	SAS_DPRINTK("port%d: class:0x%x\n", port->id, port->class);
	SAS_DPRINTK("port%d: sas_addr:%llx\n", port->id,
		    SAS_ADDR(port->sas_addr));
	SAS_DPRINTK("port%d: attached_sas_addr:%llx\n", port->id,
		    SAS_ADDR(port->attached_sas_addr));
	SAS_DPRINTK("port%d: iproto:0x%x\n", port->id, port->iproto);
	SAS_DPRINTK("port%d: tproto:0x%x\n", port->id, port->tproto);
	SAS_DPRINTK("port%d: oob_mode:0x%x\n", port->id, port->oob_mode);
	SAS_DPRINTK("port%d: num_phys:%d\n", port->id, port->num_phys);
}