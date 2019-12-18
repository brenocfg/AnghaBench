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
 int* mb_tbl_code2uni_kddi1 ; 
 int mb_tbl_code2uni_kddi1_max ; 
 int mb_tbl_code2uni_kddi1_min ; 
 int* mb_tbl_code2uni_kddi2 ; 
 int mb_tbl_code2uni_kddi2_max ; 
 int mb_tbl_code2uni_kddi2_min ; 
 int /*<<< orphan*/ ** nflags_s ; 

int
mbfilter_sjis_emoji_kddi2unicode(int s, int *snd)
{
	int w = s, si, c;
	const int nflags_order_kddi[] = {3, 1, 5, 4, 0, 7};

	*snd = 0;
	if (s >= mb_tbl_code2uni_kddi1_min && s <= mb_tbl_code2uni_kddi1_max) {
		si = s - mb_tbl_code2uni_kddi1_min;
		if (si == 0x0008) { /* ES */
			*snd = NFLAGS(nflags_s[2][0]); w = NFLAGS(nflags_s[2][1]);
		} else if (si == 0x0009) { /* RU */
			*snd = NFLAGS(nflags_s[8][0]); w = NFLAGS(nflags_s[8][1]);
		} else if (si >= 0x008d && si <= 0x0092) {
			c = nflags_order_kddi[si-0x008d];
			*snd = NFLAGS(nflags_s[c][0]); w = NFLAGS(nflags_s[c][1]);
		} else if (si == 0x0104) {
			*snd = 0x0023; w = 0x20E3;
		} else {
			w = mb_tbl_code2uni_kddi1[si];
			if (w > 0xf000) {
				w += 0x10000;
			} else if (w > 0xe000) { /* unsupported by Unicode 6.0 */
				w += 0xf0000;
			}
		}
	} else if (s >= mb_tbl_code2uni_kddi2_min && s <= mb_tbl_code2uni_kddi2_max) {
		si = s - mb_tbl_code2uni_kddi2_min;
		if (si == 100) { /* JP */
			*snd = NFLAGS(nflags_s[6][0]); w = NFLAGS(nflags_s[6][1]);
		} else if (si >= 0x00ba && si <= 0x00c2) {
			*snd = si-0x00ba+0x0031; w = 0x20E3;
		} else if (si == 0x010b) { /* US */
			*snd = NFLAGS(nflags_s[9][0]); w = NFLAGS(nflags_s[9][1]);
		} else if (si == 0x0144) {
			*snd = 0x0030; w = 0x20E3;
		} else {
			w = mb_tbl_code2uni_kddi2[si];
			if (w > 0xf000) {
				w += 0x10000;
			} else if (w > 0xe000) { /* unsupported by Unicode 6.0 */
				w += 0xf0000;
			}
		}
	}
	return w;
}