#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct TYPE_8__ {int id; int val; } ;
struct TYPE_7__ {int id; int val; } ;
struct TYPE_6__ {int id; int /*<<< orphan*/  str; } ;
struct TYPE_5__ {int id; int val; } ;

/* Variables and functions */
 int GET_WID_TYPE (int) ; 
#define  WID_CHAR 131 
#define  WID_INT 130 
 int WID_NIL ; 
#define  WID_SHORT 129 
 int WID_SITE_SURVEY_RESULTS ; 
#define  WID_STR 128 
 TYPE_4__* g_cfg_byte ; 
 TYPE_3__* g_cfg_hword ; 
 TYPE_2__* g_cfg_str ; 
 TYPE_1__* g_cfg_word ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void wilc_wlan_parse_response_frame(u8 *info, int size)
{
	u16 wid;
	u32 len = 0, i = 0;

	while (size > 0) {
		i = 0;
		wid = info[0] | (info[1] << 8);

		switch (GET_WID_TYPE(wid)) {
		case WID_CHAR:
			do {
				if (g_cfg_byte[i].id == WID_NIL)
					break;

				if (g_cfg_byte[i].id == wid) {
					g_cfg_byte[i].val = info[4];
					break;
				}
				i++;
			} while (1);
			len = 3;
			break;

		case WID_SHORT:
			do {
				if (g_cfg_hword[i].id == WID_NIL)
					break;

				if (g_cfg_hword[i].id == wid) {
					g_cfg_hword[i].val = (info[4] |
							      (info[5] << 8));
					break;
				}
				i++;
			} while (1);
			len = 4;
			break;

		case WID_INT:
			do {
				if (g_cfg_word[i].id == WID_NIL)
					break;

				if (g_cfg_word[i].id == wid) {
					g_cfg_word[i].val = (info[4] |
							     (info[5] << 8) |
							     (info[6] << 16) |
							     (info[7] << 24));
					break;
				}
				i++;
			} while (1);
			len = 6;
			break;

		case WID_STR:
			do {
				if (g_cfg_str[i].id == WID_NIL)
					break;

				if (g_cfg_str[i].id == wid) {
					if (wid == WID_SITE_SURVEY_RESULTS) {
						static int toggle;

						i += toggle;
						toggle ^= 1;
					}
					memcpy(g_cfg_str[i].str, &info[2],
					       (info[2] + 2));
					break;
				}
				i++;
			} while (1);
			len = 2 + info[2];
			break;

		default:
			break;
		}
		size -= (2 + len);
		info += (2 + len);
	}
}