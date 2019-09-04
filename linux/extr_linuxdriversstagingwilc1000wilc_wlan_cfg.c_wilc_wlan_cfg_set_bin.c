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
typedef  scalar_t__ u32 ;
typedef  int u16 ;

/* Variables and functions */
 scalar_t__ MAX_CFG_FRAME_SIZE ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static int wilc_wlan_cfg_set_bin(u8 *frame, u32 offset, u16 id, u8 *b, u32 size)
{
	u8 *buf;
	u32 i;
	u8 checksum = 0;

	if ((offset + size + 5) >= MAX_CFG_FRAME_SIZE)
		return 0;

	buf = &frame[offset];
	buf[0] = (u8)id;
	buf[1] = (u8)(id >> 8);
	buf[2] = (u8)size;
	buf[3] = (u8)(size >> 8);

	if ((b) && size != 0) {
		memcpy(&buf[4], b, size);
		for (i = 0; i < size; i++)
			checksum += buf[i + 4];
	}

	buf[size + 4] = checksum;

	return (size + 5);
}