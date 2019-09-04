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

/* Variables and functions */

__attribute__((used)) static u8 _rtl8723be_get_chnl_group(u8 chnl)
{
	u8 group;

	if (chnl < 3)
		group = 0;
	else if (chnl < 9)
		group = 1;
	else
		group = 2;
	return group;
}