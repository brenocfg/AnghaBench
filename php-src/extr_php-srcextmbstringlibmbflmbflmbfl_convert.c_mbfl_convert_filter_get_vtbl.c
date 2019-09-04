#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mbfl_convert_vtbl {scalar_t__ from; scalar_t__ to; } ;
struct TYPE_6__ {scalar_t__ no_encoding; struct mbfl_convert_vtbl const* output_filter; struct mbfl_convert_vtbl const* input_filter; } ;
typedef  TYPE_1__ mbfl_encoding ;

/* Variables and functions */
 TYPE_1__ const mbfl_encoding_8bit ; 
 TYPE_1__ const mbfl_encoding_wchar ; 
 scalar_t__ mbfl_no_encoding_7bit ; 
 scalar_t__ mbfl_no_encoding_base64 ; 
 scalar_t__ mbfl_no_encoding_qprint ; 
 scalar_t__ mbfl_no_encoding_uuencode ; 
 scalar_t__ mbfl_no_encoding_wchar ; 
 struct mbfl_convert_vtbl** mbfl_special_filter_list ; 
 struct mbfl_convert_vtbl const vtbl_pass ; 

const struct mbfl_convert_vtbl * mbfl_convert_filter_get_vtbl(
		const mbfl_encoding *from, const mbfl_encoding *to)
{
	if (to->no_encoding == mbfl_no_encoding_base64 ||
	    to->no_encoding == mbfl_no_encoding_qprint ||
	    to->no_encoding == mbfl_no_encoding_7bit) {
		from = &mbfl_encoding_8bit;
	} else if (from->no_encoding == mbfl_no_encoding_base64 ||
			   from->no_encoding == mbfl_no_encoding_qprint ||
			   from->no_encoding == mbfl_no_encoding_uuencode) {
		to = &mbfl_encoding_8bit;
	}

	if (to == from && (to == &mbfl_encoding_wchar || to == &mbfl_encoding_8bit)) {
		return &vtbl_pass;
	}

	if (to->no_encoding == mbfl_no_encoding_wchar) {
		return from->input_filter;
	} else if (from->no_encoding == mbfl_no_encoding_wchar) {
		return to->output_filter;
	} else {
		int i = 0;
		const struct mbfl_convert_vtbl *vtbl;
		while ((vtbl = mbfl_special_filter_list[i++]) != NULL){
			if (vtbl->from == from->no_encoding && vtbl->to == to->no_encoding) {
				return vtbl;
			}
		}
		return NULL;
	}
}