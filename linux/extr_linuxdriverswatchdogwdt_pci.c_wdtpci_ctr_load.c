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

/* Variables and functions */
 scalar_t__ WDT_COUNT0 ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void wdtpci_ctr_load(int ctr, int val)
{
	outb(val & 0xFF, WDT_COUNT0 + ctr);
	udelay(8);
	outb(val >> 8, WDT_COUNT0 + ctr);
	udelay(8);
}