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
struct r8152 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCU_TYPE_USB ; 
 int /*<<< orphan*/  USB_UPS_FLAGS ; 
 int /*<<< orphan*/  ocp_read_dword (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_write_dword (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r8153b_ups_flags_w1w0(struct r8152 *tp, u32 set, u32 clear)
{
	u32 ocp_data;

	ocp_data = ocp_read_dword(tp, MCU_TYPE_USB, USB_UPS_FLAGS);
	ocp_data &= ~clear;
	ocp_data |= set;
	ocp_write_dword(tp, MCU_TYPE_USB, USB_UPS_FLAGS, ocp_data);
}