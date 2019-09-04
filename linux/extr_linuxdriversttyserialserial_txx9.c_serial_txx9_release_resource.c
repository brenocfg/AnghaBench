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
struct TYPE_2__ {int iotype; int flags; int /*<<< orphan*/  iobase; int /*<<< orphan*/  mapbase; int /*<<< orphan*/ * membase; } ;
struct uart_txx9_port {TYPE_1__ port; } ;

/* Variables and functions */
 unsigned int TXX9_REGION_SIZE ; 
 int UPF_IOREMAP ; 
#define  UPIO_PORT 128 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void serial_txx9_release_resource(struct uart_txx9_port *up)
{
	unsigned int size = TXX9_REGION_SIZE;

	switch (up->port.iotype) {
	default:
		if (!up->port.mapbase)
			break;

		if (up->port.flags & UPF_IOREMAP) {
			iounmap(up->port.membase);
			up->port.membase = NULL;
		}

		release_mem_region(up->port.mapbase, size);
		break;

	case UPIO_PORT:
		release_region(up->port.iobase, size);
		break;
	}
}