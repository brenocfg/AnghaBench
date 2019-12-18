#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int status; int cache; int /*<<< orphan*/  data; int /*<<< orphan*/  (* output_function ) (int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  CK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbfl_filt_put_invalid_char (int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 

int mbfl_filt_conv_utf8_wchar(int c, mbfl_convert_filter *filter)
{
	int s, c1;

retry:
	switch (filter->status & 0xff) {
	case 0x00:
		if (c < 0x80) {
			CK((*filter->output_function)(c, filter->data));
		} else if (c >= 0xc2 && c <= 0xdf) { /* 2byte code first char: 0xc2-0xdf */
			filter->status = 0x10;
			filter->cache = c & 0x1f;
		} else if (c >= 0xe0 && c <= 0xef) { /* 3byte code first char: 0xe0-0xef */
			filter->status = 0x20;
			filter->cache = c & 0xf;
		} else if (c >= 0xf0 && c <= 0xf4) { /* 3byte code first char: 0xf0-0xf4 */
			filter->status = 0x30;
			filter->cache = c & 0x7;
		} else {
			CK(mbfl_filt_put_invalid_char(c, filter));
		}
		break;
	case 0x10: /* 2byte code 2nd char: 0x80-0xbf */
	case 0x21: /* 3byte code 3rd char: 0x80-0xbf */
	case 0x32: /* 4byte code 4th char: 0x80-0xbf */
		filter->status = 0;
		if (c >= 0x80 && c <= 0xbf) {
			s = (filter->cache<<6) | (c & 0x3f);
			filter->cache = 0;
			CK((*filter->output_function)(s, filter->data));
		} else {
			CK(mbfl_filt_put_invalid_char(filter->cache, filter));
			goto retry;
		}
		break;
	case 0x20: /* 3byte code 2nd char: 0:0xa0-0xbf,D:0x80-9F,1-C,E-F:0x80-0x9f */
		s = (filter->cache<<6) | (c & 0x3f);
		c1 = filter->cache & 0xf;

		if ((c >= 0x80 && c <= 0xbf) &&
			((c1 == 0x0 && c >= 0xa0) ||
			 (c1 == 0xd && c < 0xa0) ||
			 (c1 > 0x0 && c1 != 0xd))) {
			filter->cache = s;
			filter->status++;
		} else {
			CK(mbfl_filt_put_invalid_char(filter->cache, filter));
			goto retry;
		}
		break;
	case 0x30: /* 4byte code 2nd char: 0:0x90-0xbf,1-3:0x80-0xbf,4:0x80-0x8f */
		s = (filter->cache<<6) | (c & 0x3f);
		c1 = filter->cache & 0x7;

		if ((c >= 0x80 && c <= 0xbf) &&
			((c1 == 0x0 && c >= 0x90) ||
			 (c1 == 0x4 && c < 0x90) ||
			 (c1 > 0x0 && c1 != 0x4))) {
			filter->cache = s;
			filter->status++;
		} else {
			CK(mbfl_filt_put_invalid_char(filter->cache, filter));
			goto retry;
		}
		break;
	case 0x31: /* 4byte code 3rd char: 0x80-0xbf */
		if (c >= 0x80 && c <= 0xbf) {
			filter->cache = (filter->cache<<6) | (c & 0x3f);
			filter->status++;
		} else {
			CK(mbfl_filt_put_invalid_char(filter->cache, filter));
			goto retry;
		}
		break;
	default:
		filter->status = 0;
		break;
	}

	return c;
}