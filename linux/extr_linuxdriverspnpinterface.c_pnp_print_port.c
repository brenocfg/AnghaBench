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
struct pnp_port {int flags; scalar_t__ size; scalar_t__ align; scalar_t__ max; scalar_t__ min; } ;
typedef  int /*<<< orphan*/  pnp_info_buffer_t ;

/* Variables and functions */
 int IORESOURCE_IO_16BIT_ADDR ; 
 int /*<<< orphan*/  pnp_printf (int /*<<< orphan*/ *,char*,char*,unsigned long long,unsigned long long,unsigned long long,unsigned long long,int) ; 

__attribute__((used)) static void pnp_print_port(pnp_info_buffer_t * buffer, char *space,
			   struct pnp_port *port)
{
	pnp_printf(buffer, "%sport %#llx-%#llx, align %#llx, size %#llx, "
		   "%i-bit address decoding\n", space,
		   (unsigned long long) port->min,
		   (unsigned long long) port->max,
		   port->align ? ((unsigned long long) port->align - 1) : 0,
		   (unsigned long long) port->size,
		   port->flags & IORESOURCE_IO_16BIT_ADDR ? 16 : 10);
}