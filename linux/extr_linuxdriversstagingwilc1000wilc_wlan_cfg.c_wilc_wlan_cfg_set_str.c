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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
typedef  int u16 ;

/* Variables and functions */
 scalar_t__ MAX_CFG_FRAME_SIZE ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,size_t) ; 

__attribute__((used)) static int wilc_wlan_cfg_set_str(u8 *frame, u32 offset, u16 id, u8 *str,
				 u32 size)
{
	u8 *buf;

	if ((offset + size + 4) >= MAX_CFG_FRAME_SIZE)
		return 0;

	buf = &frame[offset];

	buf[0] = (u8)id;
	buf[1] = (u8)(id >> 8);
	buf[2] = (u8)size;
	buf[3] = (u8)(size >> 8);

	if (str && size != 0)
		memcpy(&buf[4], str, size);

	return (size + 4);
}