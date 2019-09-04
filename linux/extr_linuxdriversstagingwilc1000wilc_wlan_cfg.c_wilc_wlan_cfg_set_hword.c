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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int MAX_CFG_FRAME_SIZE ; 

__attribute__((used)) static int wilc_wlan_cfg_set_hword(u8 *frame, u32 offset, u16 id, u16 val16)
{
	u8 *buf;

	if ((offset + 5) >= MAX_CFG_FRAME_SIZE)
		return 0;

	buf = &frame[offset];

	buf[0] = (u8)id;
	buf[1] = (u8)(id >> 8);
	buf[2] = 2;
	buf[3] = 0;
	buf[4] = (u8)val16;
	buf[5] = (u8)(val16 >> 8);

	return 6;
}