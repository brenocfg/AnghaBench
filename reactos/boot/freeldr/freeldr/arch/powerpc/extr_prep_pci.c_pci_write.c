#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* cfg; } ;
typedef  TYPE_2__ pci_desc ;
struct TYPE_5__ {unsigned long addr; void* data; } ;

/* Variables and functions */
 unsigned long pci_cfg_addr (int,int,int,int) ; 
 unsigned long pci_read (TYPE_2__*,int,int,int,int,int) ; 
 void* rev32 (unsigned long) ; 
 int /*<<< orphan*/  sync () ; 

void pci_write( pci_desc *desc, int bus, int dev, int fn, int reg, int len, int val ) {
    unsigned long save_state = desc->cfg->addr;
    unsigned long addr = pci_cfg_addr(bus,dev,fn,reg);
    unsigned long offset = reg & 3;
    unsigned long oldval = pci_read( desc, bus, dev, fn, reg & ~3, 4 );
    unsigned long mask = ((1 << (len * 8)) - 1) << (offset << 3);
    oldval = (oldval & ~mask) | ((val << (offset << 3)) & mask);
    desc->cfg->addr = rev32(addr);
    sync();
    desc->cfg->data = rev32(oldval);
    sync();
    desc->cfg->addr = save_state;
    sync();
}