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
struct TYPE_3__ {int cache; int status; int (* flush_function ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; int /*<<< orphan*/  (* output_function ) (int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  CK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ) ; 

int
mbfl_filt_conv_sjis_mobile_flush(mbfl_convert_filter *filter)
{
	int c1 = filter->cache;
	if (filter->status == 1 && (c1 == 0x0023 || (c1 >= 0x0030 && c1<=0x0039))) {
		CK((*filter->output_function)(c1, filter->data));
	}
	filter->status = 0;
	filter->cache = 0;

	if (filter->flush_function != NULL) {
		return (*filter->flush_function)(filter->data);
	}

	return 0;
}