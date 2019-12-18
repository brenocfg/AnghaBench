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
struct TYPE_3__ {int status; int cache; int /*<<< orphan*/  data; int /*<<< orphan*/  (* flush_function ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* output_function ) (int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  CK (int /*<<< orphan*/ ) ; 
 int* mbfl_base64_table ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int,int /*<<< orphan*/ ) ; 

int mbfl_filt_conv_wchar_utf7_flush(mbfl_convert_filter *filter)
{
	int status, cache;

	status = filter->status;
	cache = filter->cache;
	filter->status = 0;
	filter->cache = 0;
	/* flush fragments */
	switch (status) {
	case 1:
		CK((*filter->output_function)(mbfl_base64_table[(cache >> 10) & 0x3f], filter->data));
		CK((*filter->output_function)(mbfl_base64_table[(cache >> 4) & 0x3f], filter->data));
		CK((*filter->output_function)(mbfl_base64_table[(cache << 2) & 0x3c], filter->data));
		CK((*filter->output_function)(0x2d, filter->data));		/* '-' */
		break;

	case 2:
		CK((*filter->output_function)(mbfl_base64_table[(cache >> 14) & 0x3f], filter->data));
		CK((*filter->output_function)(mbfl_base64_table[(cache >> 8) & 0x3f], filter->data));
		CK((*filter->output_function)(mbfl_base64_table[(cache >> 2) & 0x3f], filter->data));
		CK((*filter->output_function)(mbfl_base64_table[(cache << 4) & 0x30], filter->data));
		CK((*filter->output_function)(0x2d, filter->data));		/* '-' */
		break;

	case 3:
		CK((*filter->output_function)(mbfl_base64_table[(cache >> 12) & 0x3f], filter->data));
		CK((*filter->output_function)(mbfl_base64_table[(cache >> 6) & 0x3f], filter->data));
		CK((*filter->output_function)(mbfl_base64_table[cache & 0x3f], filter->data));
		CK((*filter->output_function)(0x2d, filter->data));		/* '-' */
		break;
	}

	if (filter->flush_function != NULL) {
		(*filter->flush_function)(filter->data);
	}

	return 0;
}