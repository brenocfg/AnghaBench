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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;

/* Variables and functions */
#define  CFG_BIN_CMD 132 
#define  CFG_BYTE_CMD 131 
#define  CFG_HWORD_CMD 130 
#define  CFG_STR_CMD 129 
#define  CFG_WORD_CMD 128 
 int wilc_wlan_cfg_set_bin (int*,int /*<<< orphan*/ ,int,int*,int) ; 
 int wilc_wlan_cfg_set_byte (int*,int /*<<< orphan*/ ,int,int) ; 
 int wilc_wlan_cfg_set_hword (int*,int /*<<< orphan*/ ,int,int) ; 
 int wilc_wlan_cfg_set_str (int*,int /*<<< orphan*/ ,int,int*,int) ; 
 int wilc_wlan_cfg_set_word (int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int wilc_wlan_cfg_set_wid(u8 *frame, u32 offset, u16 id, u8 *buf, int size)
{
	u8 type = (id >> 12) & 0xf;
	int ret = 0;

	switch (type) {
	case CFG_BYTE_CMD:
		if (size >= 1)
			ret = wilc_wlan_cfg_set_byte(frame, offset, id, *buf);
		break;

	case CFG_HWORD_CMD:
		if (size >= 2)
			ret = wilc_wlan_cfg_set_hword(frame, offset, id,
						      *((u16 *)buf));
		break;

	case CFG_WORD_CMD:
		if (size >= 4)
			ret = wilc_wlan_cfg_set_word(frame, offset, id,
						     *((u32 *)buf));
		break;

	case CFG_STR_CMD:
		ret = wilc_wlan_cfg_set_str(frame, offset, id, buf, size);
		break;

	case CFG_BIN_CMD:
		ret = wilc_wlan_cfg_set_bin(frame, offset, id, buf, size);
		break;
	}

	return ret;
}