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
struct TYPE_4__ {int status; scalar_t__ cache; int /*<<< orphan*/  (* filter_function ) (char,TYPE_1__*) ;} ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (char,TYPE_1__*) ; 

int mbfl_filt_conv_qprintenc_flush(mbfl_convert_filter *filter)
{
	/* flush filter cache */
	(*filter->filter_function)('\0', filter);
	filter->status &= ~0xffff;
	filter->cache = 0;
	return 0;
}