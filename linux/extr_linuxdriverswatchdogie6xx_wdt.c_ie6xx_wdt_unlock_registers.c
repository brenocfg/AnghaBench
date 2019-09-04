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
struct TYPE_2__ {scalar_t__ sch_wdtba; } ;

/* Variables and functions */
 scalar_t__ RR0 ; 
 TYPE_1__ ie6xx_wdt_data ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void ie6xx_wdt_unlock_registers(void)
{
	outb(0x80, ie6xx_wdt_data.sch_wdtba + RR0);
	outb(0x86, ie6xx_wdt_data.sch_wdtba + RR0);
}