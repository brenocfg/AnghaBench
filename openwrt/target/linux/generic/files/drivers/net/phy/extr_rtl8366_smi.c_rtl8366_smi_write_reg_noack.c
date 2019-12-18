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
typedef  int /*<<< orphan*/  u32 ;
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int __rtl8366_smi_write_reg (struct rtl8366_smi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int rtl8366_smi_write_reg_noack(struct rtl8366_smi *smi, u32 addr, u32 data)
{
	return __rtl8366_smi_write_reg(smi, addr, data, false);
}