#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int status; scalar_t__ cache; int /*<<< orphan*/  data; int /*<<< orphan*/  (* output_function ) (int,int /*<<< orphan*/ ) ;TYPE_1__* to; } ;
typedef  TYPE_2__ mbfl_convert_filter ;
struct TYPE_8__ {scalar_t__ no_encoding; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK (int /*<<< orphan*/ ) ; 
 scalar_t__ mbfilter_conv_map_tbl (int,int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mbfilter_unicode2sjis_emoji_docomo (int,int*,TYPE_2__*) ; 
 scalar_t__ mbfilter_unicode2sjis_emoji_kddi (int,int*,TYPE_2__*) ; 
 scalar_t__ mbfilter_unicode2sjis_emoji_sb (int,int*,TYPE_2__*) ; 
 int /*<<< orphan*/  mbfl_docomo2uni_pua ; 
 int /*<<< orphan*/  mbfl_filt_conv_illegal_output (int,TYPE_2__*) ; 
 int /*<<< orphan*/  mbfl_kddi2uni_pua ; 
 int /*<<< orphan*/  mbfl_kddi2uni_pua_b ; 
 scalar_t__ mbfl_no_encoding_utf8_docomo ; 
 scalar_t__ mbfl_no_encoding_utf8_kddi_a ; 
 scalar_t__ mbfl_no_encoding_utf8_kddi_b ; 
 scalar_t__ mbfl_no_encoding_utf8_sb ; 
 int /*<<< orphan*/  mbfl_sb2uni_pua ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int,int /*<<< orphan*/ ) ; 

int mbfl_filt_conv_wchar_utf8_mobile(int c, mbfl_convert_filter *filter)
{
	if (c >= 0 && c < 0x110000) {
		int s1, c1;

		if ((filter->to->no_encoding == mbfl_no_encoding_utf8_docomo &&
			 mbfilter_unicode2sjis_emoji_docomo(c, &s1, filter) > 0 &&
			 mbfilter_conv_map_tbl(s1, &c1, mbfl_docomo2uni_pua, 4) > 0) ||
			(filter->to->no_encoding == mbfl_no_encoding_utf8_kddi_a &&
			 mbfilter_unicode2sjis_emoji_kddi(c, &s1, filter) > 0 &&
			 mbfilter_conv_map_tbl(s1, &c1, mbfl_kddi2uni_pua, 7) > 0) ||
			(filter->to->no_encoding == mbfl_no_encoding_utf8_kddi_b &&
			 mbfilter_unicode2sjis_emoji_kddi(c, &s1, filter) > 0 &&
			 mbfilter_conv_map_tbl(s1, &c1, mbfl_kddi2uni_pua_b, 8) > 0) ||
			(filter->to->no_encoding == mbfl_no_encoding_utf8_sb &&
			 mbfilter_unicode2sjis_emoji_sb(c, &s1, filter) > 0 &&
			 mbfilter_conv_map_tbl(s1, &c1, mbfl_sb2uni_pua, 6) > 0)) {
			c = c1;
		}

		if (filter->status == 1 && filter->cache > 0) {
			return c;
		}

		if (c < 0x80) {
			CK((*filter->output_function)(c, filter->data));
		} else if (c < 0x800) {
			CK((*filter->output_function)(((c >> 6) & 0x1f) | 0xc0, filter->data));
			CK((*filter->output_function)((c & 0x3f) | 0x80, filter->data));
		} else if (c < 0x10000) {
			CK((*filter->output_function)(((c >> 12) & 0x0f) | 0xe0, filter->data));
			CK((*filter->output_function)(((c >> 6) & 0x3f) | 0x80, filter->data));
			CK((*filter->output_function)((c & 0x3f) | 0x80, filter->data));
		} else {
			CK((*filter->output_function)(((c >> 18) & 0x07) | 0xf0, filter->data));
			CK((*filter->output_function)(((c >> 12) & 0x3f) | 0x80, filter->data));
			CK((*filter->output_function)(((c >> 6) & 0x3f) | 0x80, filter->data));
			CK((*filter->output_function)((c & 0x3f) | 0x80, filter->data));
		}
	} else {
		CK(mbfl_filt_conv_illegal_output(c, filter));
	}

	return c;
}