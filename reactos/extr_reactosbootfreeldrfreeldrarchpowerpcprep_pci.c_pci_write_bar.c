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
struct _pci_bar {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  pci_desc ;

/* Variables and functions */
 int /*<<< orphan*/  pci_write (int /*<<< orphan*/ *,int,int,int,int,int,int /*<<< orphan*/ ) ; 

void pci_write_bar( pci_desc *desc, int bus, int dev, int fn, int bar, struct _pci_bar *bar_data ) {
    pci_write( desc, bus, dev, fn, 0x10 + (bar * 4), 4, bar_data->data );
}