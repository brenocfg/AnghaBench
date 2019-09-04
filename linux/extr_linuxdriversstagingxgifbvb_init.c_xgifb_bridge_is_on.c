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
typedef  int u8 ;
struct vb_device_info {int /*<<< orphan*/  Part4Port; } ;

/* Variables and functions */
 int xgifb_reg_get (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool xgifb_bridge_is_on(struct vb_device_info *vb_info)
{
	u8 flag;

	flag = xgifb_reg_get(vb_info->Part4Port, 0x00);
	return flag == 1 || flag == 2;
}