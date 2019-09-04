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

__attribute__((used)) static void imm_reset_pulse(unsigned int base)
{
	w_ctr(base, 0x04);
	w_dtr(base, 0x40);
	udelay(1);
	w_ctr(base, 0x0c);
	w_ctr(base, 0x0d);
	udelay(50);
	w_ctr(base, 0x0c);
	w_ctr(base, 0x04);
}