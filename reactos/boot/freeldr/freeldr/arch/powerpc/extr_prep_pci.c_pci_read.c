#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* cfg; } ;
typedef  TYPE_2__ pci_desc ;
struct TYPE_4__ {unsigned long addr; unsigned long data; } ;

/* Variables and functions */
 unsigned long pci_cfg_addr (int,int,int,int) ; 
 unsigned long rev32 (unsigned long) ; 
 int /*<<< orphan*/  sync () ; 

unsigned long pci_read( pci_desc *desc, int bus, int dev, int fn, int reg, int len ) {
    sync();
    unsigned long save_state = desc->cfg->addr, ret = 0;
    unsigned long addr = pci_cfg_addr(bus,dev,fn,reg);
    unsigned long offset = reg & 3;
    desc->cfg->addr = rev32(addr);
    sync();
    switch( len ) {
    case 4:
        ret = desc->cfg->data;
        break;
    case 2:
        ret = desc->cfg->data;
        ret = (ret >> (offset << 3)) & 0xffff;
        break;
    case 1:
        ret = desc->cfg->data;
        ret = (ret >> (offset << 3)) & 0xff;
        break;
    }
    desc->cfg->addr = save_state;
    sync();
    return ret;
    }