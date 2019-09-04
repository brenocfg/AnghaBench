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
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  w_ctr (unsigned int,int) ; 
 int /*<<< orphan*/  w_dtr (unsigned int,int) ; 

__attribute__((used)) static void ppa_reset_pulse(unsigned int base)
{
	w_dtr(base, 0x40);
	w_ctr(base, 0x8);
	udelay(30);
	w_ctr(base, 0xc);
}