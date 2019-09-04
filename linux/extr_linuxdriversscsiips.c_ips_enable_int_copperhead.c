#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ io_addr; } ;
typedef  TYPE_1__ ips_ha_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPS_BIT_EI ; 
 scalar_t__ IPS_REG_HISR ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ips_enable_int_copperhead(ips_ha_t * ha)
{
	METHOD_TRACE("ips_enable_int_copperhead", 1);

	outb(ha->io_addr + IPS_REG_HISR, IPS_BIT_EI);
	inb(ha->io_addr + IPS_REG_HISR);	/*Ensure PCI Posting Completes*/
}