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
 int* mb_tbl_code2uni_docomo1 ; 
 int mb_tbl_code2uni_docomo1_max ; 
 int mb_tbl_code2uni_docomo1_min ; 

int
mbfilter_sjis_emoji_docomo2unicode(int s, int *snd)
{
	int w = s;
	if (s >= mb_tbl_code2uni_docomo1_min && s <= mb_tbl_code2uni_docomo1_max) {
		if (s >= mb_tbl_code2uni_docomo1_min + 0x00a2 &&
			s <= mb_tbl_code2uni_docomo1_min + 0x00ad &&
			s != mb_tbl_code2uni_docomo1_min + 0x00a3) {
			w =  0x20E3;
			*snd = mb_tbl_code2uni_docomo1[s - mb_tbl_code2uni_docomo1_min];
			if (*snd > 0xf000) {
				*snd += 0x10000;
			}
		} else {
			w = mb_tbl_code2uni_docomo1[s - mb_tbl_code2uni_docomo1_min];
			if (w > 0xf000) {
				w += 0x10000;
			} else if (w > 0xe000) { /* unsupported by Unicode 6.0 */
				w += 0xf0000;
			}
			*snd = 0;
			if (!w) {
				w = s;
			}
		}
	}

	return w;
}