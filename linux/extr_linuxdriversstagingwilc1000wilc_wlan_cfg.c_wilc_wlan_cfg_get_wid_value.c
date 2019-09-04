#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_10__ {scalar_t__ id; int val; } ;
struct TYPE_9__ {scalar_t__ id; int val; } ;
struct TYPE_8__ {scalar_t__ id; int* str; } ;
struct TYPE_7__ {scalar_t__ id; int val; } ;
struct TYPE_6__ {scalar_t__ mac_status; } ;

/* Variables and functions */
 scalar_t__ CFG_BYTE_CMD ; 
 scalar_t__ CFG_HWORD_CMD ; 
 scalar_t__ CFG_STR_CMD ; 
 scalar_t__ CFG_WORD_CMD ; 
 scalar_t__ WID_NIL ; 
 scalar_t__ WID_SITE_SURVEY_RESULTS ; 
 int WID_STATUS ; 
 TYPE_5__* g_cfg_byte ; 
 TYPE_4__* g_cfg_hword ; 
 TYPE_3__* g_cfg_str ; 
 TYPE_2__* g_cfg_word ; 
 TYPE_1__ g_mac ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,scalar_t__) ; 

int wilc_wlan_cfg_get_wid_value(u16 wid, u8 *buffer, u32 buffer_size)
{
	u32 type = (wid >> 12) & 0xf;
	int i, ret = 0;

	if (wid == WID_STATUS) {
		*((u32 *)buffer) = g_mac.mac_status;
		return 4;
	}

	i = 0;
	if (type == CFG_BYTE_CMD) {
		do {
			if (g_cfg_byte[i].id == WID_NIL)
				break;

			if (g_cfg_byte[i].id == wid) {
				memcpy(buffer,  &g_cfg_byte[i].val, 1);
				ret = 1;
				break;
			}
			i++;
		} while (1);
	} else if (type == CFG_HWORD_CMD) {
		do {
			if (g_cfg_hword[i].id == WID_NIL)
				break;

			if (g_cfg_hword[i].id == wid) {
				memcpy(buffer,  &g_cfg_hword[i].val, 2);
				ret = 2;
				break;
			}
			i++;
		} while (1);
	} else if (type == CFG_WORD_CMD) {
		do {
			if (g_cfg_word[i].id == WID_NIL)
				break;

			if (g_cfg_word[i].id == wid) {
				memcpy(buffer,  &g_cfg_word[i].val, 4);
				ret = 4;
				break;
			}
			i++;
		} while (1);
	} else if (type == CFG_STR_CMD) {
		do {
			u32 id = g_cfg_str[i].id;

			if (id == WID_NIL)
				break;

			if (id == wid) {
				u32 size = g_cfg_str[i].str[0] |
						(g_cfg_str[i].str[1] << 8);

				if (buffer_size >= size) {
					if (id == WID_SITE_SURVEY_RESULTS) {
						static int toggle;

						i += toggle;
						toggle ^= 1;
					}
					memcpy(buffer,  &g_cfg_str[i].str[2],
					       size);
					ret = size;
				}
				break;
			}
			i++;
		} while (1);
	}

	return ret;
}