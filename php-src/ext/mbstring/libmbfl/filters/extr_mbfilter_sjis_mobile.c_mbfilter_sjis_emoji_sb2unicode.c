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

/* Variables and functions */
 int NFLAGS (int /*<<< orphan*/ ) ; 
 int* mb_tbl_code2uni_sb1 ; 
 int mb_tbl_code2uni_sb1_max ; 
 int mb_tbl_code2uni_sb1_min ; 
 int* mb_tbl_code2uni_sb2 ; 
 int mb_tbl_code2uni_sb2_max ; 
 int mb_tbl_code2uni_sb2_min ; 
 int* mb_tbl_code2uni_sb3 ; 
 int mb_tbl_code2uni_sb3_max ; 
 int mb_tbl_code2uni_sb3_min ; 
 int /*<<< orphan*/ ** nflags_s ; 

int
mbfilter_sjis_emoji_sb2unicode(int s, int *snd)
{
	int w = s, si, c;
	const int nflags_order_sb[10] = {6, 9, 3, 1, 5, 4, 2, 8, 0, 7};

	*snd = 0;
	if (s >= mb_tbl_code2uni_sb1_min &&	s <= mb_tbl_code2uni_sb1_max) {
		si = s - mb_tbl_code2uni_sb1_min;
		if (si == 0x006e || (si >= 0x007a && si <= 0x0083)) {
			*snd =  mb_tbl_code2uni_sb1[si];
			if (*snd > 0xf000) {
				*snd += 0x10000;
			}
			w = 0x20E3;
		} else {
			w = mb_tbl_code2uni_sb1[si];
			if (w > 0xf000) {
				w += 0x10000;
			} else if (w > 0xe000) { /* unsupported by Unicode 6.0 */
				w += 0xf0000;
			}
		}
	} else if (s >= mb_tbl_code2uni_sb2_min && s <= mb_tbl_code2uni_sb2_max) {
		si = s - mb_tbl_code2uni_sb2_min;
		w = mb_tbl_code2uni_sb2[si];
		if (w > 0xf000) {
			w += 0x10000;
		} else if (w > 0xe000) { /* unsupported by Unicode 6.0 */
			w += 0xf0000;
		}
	} else if (s >= mb_tbl_code2uni_sb3_min && s <= mb_tbl_code2uni_sb3_max) {
		si = s - mb_tbl_code2uni_sb3_min;
		if (si >= 0x0069 && si <= 0x0072) {
			c = nflags_order_sb[si-0x0069];
			*snd = NFLAGS(nflags_s[c][0]); w = NFLAGS(nflags_s[c][1]);
		} else {
			w = mb_tbl_code2uni_sb3[si];
			if (w > 0xf000) {
				w += 0x10000;
			} else if (w > 0xe000) { /* unsupported by Unicode 6.0 */
				w += 0xf0000;
			}
		}
	}
	return w;
}