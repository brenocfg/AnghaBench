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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ in_be32 (scalar_t__*) ; 
 int /*<<< orphan*/  out_be32 (scalar_t__*,scalar_t__) ; 

void wr_reg_wa(u32 *reg, u32 val)
{
	do {
		out_be32(reg, val);
	} while (in_be32(reg) != val);
}