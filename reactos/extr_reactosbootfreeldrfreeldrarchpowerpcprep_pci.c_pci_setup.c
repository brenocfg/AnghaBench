#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pci_desc ;
typedef  int /*<<< orphan*/  pci_cfg ;
struct TYPE_2__ {int /*<<< orphan*/ * cfg; } ;
typedef  int /*<<< orphan*/  PCONFIGURATION_COMPONENT_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_BASECLASS ; 
 int /*<<< orphan*/  PCI_DEVICEID ; 
 int /*<<< orphan*/  PCI_HEADER_TYPE ; 
 int /*<<< orphan*/  PCI_VENDORID ; 
 TYPE_1__ pci1_desc ; 
 void* pci_read (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  vga1_desc ; 
 int /*<<< orphan*/  vga_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 

void pci_setup( PCONFIGURATION_COMPONENT_DATA pcibus, pci_desc *desc ) {
    unsigned char type;
    unsigned short vendor, device, devclass;
    int funcs, bus, dev, fn;

    pci1_desc.cfg = (pci_cfg *)0x80000cf8;

    printf("PCI Bus:\n");
    for( bus = 0; bus < 1; bus++ ) {
        for( dev = 0; dev < 32; dev++ ) {
            type = pci_read(desc,bus,dev,0,PCI_HEADER_TYPE,1);
            vendor = pci_read(desc,bus,dev,0,PCI_VENDORID,2);
            device = pci_read(desc,bus,dev,0,PCI_DEVICEID,2);

            if(vendor == 0 || vendor == 0xffff) continue;
            if(type & 0x80) funcs = 8; else funcs = 1;

            for( fn = 0; fn < funcs; fn++ ) {
                devclass = pci_read(desc,bus,dev,fn,PCI_BASECLASS,1);
        printf(" %d:%d -> vendor:device:class %x:%x:%x\n",
               bus, dev, vendor, device, devclass);

                if( devclass == 3 ) {
            printf("Setting up vga...\n");
                    vga_setup(pcibus,desc,&vga1_desc,bus,dev,fn);
            printf("Done with vga\n");
                }
            }
        }
    }
    printf("^-- end PCI\n");
}