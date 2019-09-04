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
 int MBFL_BASE64_STS_MIME_HEADER ; 
 int* mbfl_base64_table ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int,int /*<<< orphan*/ ) ; 

int mbfl_filt_conv_base64enc_flush(mbfl_convert_filter *filter)
{
	int status, cache, len;

	status = filter->status & 0xff;
	cache = filter->cache;
	len = (filter->status & 0xff00) >> 8;
	filter->status &= ~0xffff;
	filter->cache = 0;
	/* flush fragments */
	if (status >= 1) {
		if ((filter->status & MBFL_BASE64_STS_MIME_HEADER) == 0) {
			if (len > 72){
				CK((*filter->output_function)(0x0d, filter->data));		/* CR */
				CK((*filter->output_function)(0x0a, filter->data));		/* LF */
			}
		}
		CK((*filter->output_function)(mbfl_base64_table[(cache >> 18) & 0x3f], filter->data));
		CK((*filter->output_function)(mbfl_base64_table[(cache >> 12) & 0x3f], filter->data));
		if (status == 1) {
			CK((*filter->output_function)(0x3d, filter->data));		/* '=' */
			CK((*filter->output_function)(0x3d, filter->data));		/* '=' */
		} else {
			CK((*filter->output_function)(mbfl_base64_table[(cache >> 6) & 0x3f], filter->data));
			CK((*filter->output_function)(0x3d, filter->data));		/* '=' */
		}
	}
	return 0;
}