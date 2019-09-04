#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int status; int cache; int /*<<< orphan*/  data; int /*<<< orphan*/  (* output_function ) (int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  CK (int /*<<< orphan*/ ) ; 
 int NFLAGS (int) ; 
 int /*<<< orphan*/  mb_tbl_uni_sb2code2_key ; 
 int /*<<< orphan*/  mb_tbl_uni_sb2code2_len ; 
 int mb_tbl_uni_sb2code2_max ; 
 int mb_tbl_uni_sb2code2_min ; 
 int* mb_tbl_uni_sb2code2_value ; 
 int /*<<< orphan*/  mb_tbl_uni_sb2code3_key ; 
 int /*<<< orphan*/  mb_tbl_uni_sb2code3_len ; 
 int mb_tbl_uni_sb2code3_max ; 
 int mb_tbl_uni_sb2code3_min ; 
 int* mb_tbl_uni_sb2code3_value ; 
 int /*<<< orphan*/  mb_tbl_uni_sb2code5_key ; 
 int /*<<< orphan*/  mb_tbl_uni_sb2code5_len ; 
 int mb_tbl_uni_sb2code5_max ; 
 int mb_tbl_uni_sb2code5_min ; 
 int* mb_tbl_uni_sb2code5_val ; 
 int mbfl_bisec_srch2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* nflags_code_sb ; 
 int** nflags_s ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int* ucs_a1_jis_table ; 
 int ucs_a1_jis_table_max ; 
 int ucs_a1_jis_table_min ; 

int
mbfilter_unicode2sjis_emoji_sb(int c, int *s1, mbfl_convert_filter *filter)
{
	int i, match = 0, c1s;

	if (filter->status == 1) {
		filter->status = 0;
		c1s = filter->cache;
		filter->cache = 0;
		if (c == 0x20E3) {
			if (c1s == 0x0023) {
				*s1 = 0x2817;
				match = 1;
			} else if (c1s == 0x0030) {
				*s1 = 0x282c;
				match = 1;
			} else if (c1s >= 0x0031 && c1s <= 0x0039) {
				*s1 = 0x2823 + (c1s - 0x0031);
				match = 1;
			}
		} else if ((c >= NFLAGS(0x41) && c <= NFLAGS(0x5A)) && (c1s >= NFLAGS(0x41) && c1s <= NFLAGS(0x5A))) {
			for (i=0; i<10; i++) {
				if (c1s == NFLAGS(nflags_s[i][0]) && c == NFLAGS(nflags_s[i][1])) {
					*s1 = nflags_code_sb[i];
					match = 1;
					break;
				}
			}
		} else {
			if (c1s >= ucs_a1_jis_table_min && c1s < ucs_a1_jis_table_max) {
				c1s = ucs_a1_jis_table[c1s - ucs_a1_jis_table_min];
				CK((*filter->output_function)(c1s, filter->data));
			}
		}
	} else {
		if (c == 0x0023 || ( c >= 0x0030 && c<=0x0039) || (c >= NFLAGS(0x41) && c<= NFLAGS(0x5A))) {
			filter->status = 1;
			filter->cache = c;
			*s1 = -1;
			return match;
		}

		if (c == 0x00A9) {
			*s1 = 0x2855; match = 1;
		} else if (c == 0x00AE) {
			*s1 = 0x2856; match = 1;
		} else if (c >= mb_tbl_uni_sb2code2_min && c <= mb_tbl_uni_sb2code2_max) {
			i = mbfl_bisec_srch2(c, mb_tbl_uni_sb2code2_key, mb_tbl_uni_sb2code2_len);
			if (i >= 0) {
				*s1 = mb_tbl_uni_sb2code2_value[i];
				match = 1;
			}
		} else if (c >= mb_tbl_uni_sb2code3_min && c <= mb_tbl_uni_sb2code3_max) {
			i = mbfl_bisec_srch2(c - 0x10000, mb_tbl_uni_sb2code3_key, mb_tbl_uni_sb2code3_len);
			if (i >= 0) {
				*s1 = mb_tbl_uni_sb2code3_value[i];
				match = 1;
			}
		} else if (c >= mb_tbl_uni_sb2code5_min && c <= mb_tbl_uni_sb2code5_max) {
			i = mbfl_bisec_srch2(c - 0xf0000, mb_tbl_uni_sb2code5_key, mb_tbl_uni_sb2code5_len);
			if (i >= 0) {
				*s1 = mb_tbl_uni_sb2code5_val[i];
				match = 1;
			}
		}
	}
	return match;
}