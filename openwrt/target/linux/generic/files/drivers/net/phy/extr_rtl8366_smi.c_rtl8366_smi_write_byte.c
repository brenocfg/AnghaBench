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
typedef  int /*<<< orphan*/  u8 ;
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int rtl8366_smi_wait_for_ack (struct rtl8366_smi*) ; 
 int /*<<< orphan*/  rtl8366_smi_write_bits (struct rtl8366_smi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtl8366_smi_write_byte(struct rtl8366_smi *smi, u8 data)
{
	rtl8366_smi_write_bits(smi, data, 8);
	return rtl8366_smi_wait_for_ack(smi);
}