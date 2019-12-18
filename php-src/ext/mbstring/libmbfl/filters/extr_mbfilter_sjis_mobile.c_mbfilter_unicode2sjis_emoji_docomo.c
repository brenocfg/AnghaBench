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
 int /*<<< orphan*/  mb_tbl_uni_docomo2code2_key ; 
 int /*<<< orphan*/  mb_tbl_uni_docomo2code2_len ; 
 int mb_tbl_uni_docomo2code2_max ; 
 int mb_tbl_uni_docomo2code2_min ; 
 int* mb_tbl_uni_docomo2code2_value ; 
 int /*<<< orphan*/  mb_tbl_uni_docomo2code3_key ; 
 int /*<<< orphan*/  mb_tbl_uni_docomo2code3_len ; 
 int mb_tbl_uni_docomo2code3_max ; 
 int mb_tbl_uni_docomo2code3_min ; 
 int* mb_tbl_uni_docomo2code3_value ; 
 int /*<<< orphan*/  mb_tbl_uni_docomo2code5_key ; 
 int /*<<< orphan*/  mb_tbl_uni_docomo2code5_len ; 
 int mb_tbl_uni_docomo2code5_max ; 
 int mb_tbl_uni_docomo2code5_min ; 
 int* mb_tbl_uni_docomo2code5_val ; 
 int mbfl_bisec_srch2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

int
mbfilter_unicode2sjis_emoji_docomo(int c, int *s1, mbfl_convert_filter *filter)
{
	int i, match = 0, c1s;

	if (filter->status == 1) {
		c1s = filter->cache;
		filter->cache = 0;
		filter->status = 0;
		if (c == 0x20E3) {
			if (c1s == 0x0023) {
				*s1 = 0x2964;
				match = 1;
			} else if (c1s == 0x0030) {
				*s1 = 0x296f;
				match = 1;
			} else if (c1s >= 0x0031 && c1s <= 0x0039) {
				*s1 = 0x2966 + (c1s - 0x0031);
				match = 1;
			}
		} else {
			CK((*filter->output_function)(c1s, filter->data));
		}
	} else {
		if (c == 0x0023 || (c >= 0x0030 && c<=0x0039)) {
			filter->status = 1;
			filter->cache = c;
			*s1 = -1;
			return match;
		}

		if (c == 0x00A9) {
			*s1 = 0x29b5; match = 1;
		} else if (c == 0x00AE) {
			*s1 = 0x29ba; match = 1;
		} else if (c >= mb_tbl_uni_docomo2code2_min && c <= mb_tbl_uni_docomo2code2_max) {
			i = mbfl_bisec_srch2(c, mb_tbl_uni_docomo2code2_key, mb_tbl_uni_docomo2code2_len);
			if (i >= 0) {
				*s1 = mb_tbl_uni_docomo2code2_value[i];
				match = 1;
			}
		} else if (c >= mb_tbl_uni_docomo2code3_min && c <= mb_tbl_uni_docomo2code3_max) {
			i = mbfl_bisec_srch2(c - 0x10000, mb_tbl_uni_docomo2code3_key, mb_tbl_uni_docomo2code3_len);
			if (i >= 0) {
				*s1 = mb_tbl_uni_docomo2code3_value[i];
				match = 1;
			}
		} else if (c >= mb_tbl_uni_docomo2code5_min && c <= mb_tbl_uni_docomo2code5_max) {
			i = mbfl_bisec_srch2(c - 0xf0000, mb_tbl_uni_docomo2code5_key, mb_tbl_uni_docomo2code5_len);
			if (i >= 0) {
				*s1 = mb_tbl_uni_docomo2code5_val[i];
				match = 1;
			}
		}
	}

	return match;
}