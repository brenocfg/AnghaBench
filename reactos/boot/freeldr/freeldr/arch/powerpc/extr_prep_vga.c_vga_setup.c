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
struct _vga_desc {char* addr; } ;
struct _pci_desc {int dummy; } ;
struct _pci_bar {int data; } ;
typedef  int /*<<< orphan*/  PCONFIGURATION_COMPONENT_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_bar (struct _pci_desc*,int,int,int,int,struct _pci_bar*) ; 
 int /*<<< orphan*/  print_bar (struct _pci_bar*) ; 

void vga_setup( PCONFIGURATION_COMPONENT_DATA pcibus,
                struct _pci_desc *desc, struct _vga_desc *vga_desc,
        int bus, int dev, int fn ) {
    struct _pci_bar bar_data;
    int i;

    for( i = 0; i < 6; i++ ) {
        pci_read_bar( desc, bus, dev, fn, i, &bar_data );
        print_bar( &bar_data );
        if( (bar_data.data > 0x10000) || ((bar_data.data&1) == 1) ) {
            vga_desc->addr = (char *)(0xc0000000 + (bar_data.data & ~0x7ff));
//        BootInfo.dispDeviceBase = vga_desc->addr;
            break;
        }
    }
}