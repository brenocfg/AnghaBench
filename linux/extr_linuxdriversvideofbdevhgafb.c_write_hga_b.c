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
 int /*<<< orphan*/  HGA_INDEX_PORT ; 
 int /*<<< orphan*/  HGA_VALUE_PORT ; 
 int /*<<< orphan*/  outb_p (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_hga_b(unsigned int val, unsigned char reg)
{
	outb_p(reg, HGA_INDEX_PORT); 
	outb_p(val, HGA_VALUE_PORT);
}