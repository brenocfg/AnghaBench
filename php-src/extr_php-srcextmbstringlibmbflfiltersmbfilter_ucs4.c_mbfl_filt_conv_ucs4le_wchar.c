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
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

int mbfl_filt_conv_ucs4le_wchar(int c, mbfl_convert_filter *filter)
{
	int n;

	if (filter->status == 0) {
		filter->status = 1;
		n = (c & 0xff);
		filter->cache = n;
	} else if (filter->status == 1) {
		filter->status = 2;
		n = (c & 0xff) << 8;
		filter->cache |= n;
	} else if (filter->status == 2) {
		filter->status = 3;
		n = (c & 0xff) << 16;
		filter->cache |= n;
	} else {
		filter->status = 0;
		n = ((c & 0xff) << 24) | filter->cache;
		CK((*filter->output_function)(n, filter->data));
	}
	return c;
}