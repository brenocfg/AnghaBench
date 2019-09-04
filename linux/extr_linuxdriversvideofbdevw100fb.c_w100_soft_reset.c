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
typedef  int u16 ;

/* Variables and functions */
 int cfgSTATUS ; 
 int readw (int*) ; 
 scalar_t__ remapped_base ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writew (int,int*) ; 

__attribute__((used)) static void w100_soft_reset(void)
{
	u16 val = readw((u16 *) remapped_base + cfgSTATUS);
	writew(val | 0x08, (u16 *) remapped_base + cfgSTATUS);
	udelay(100);
	writew(0x00, (u16 *) remapped_base + cfgSTATUS);
	udelay(100);
}