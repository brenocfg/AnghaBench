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
struct TYPE_3__ {int (* filter_flush ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int stub1 (TYPE_1__*) ; 

int mbfl_filter_output_pipe_flush(void *data)
{
	mbfl_convert_filter *filter = (mbfl_convert_filter*)data;
	if (filter->filter_flush != NULL) {
		return (*filter->filter_flush)(filter);
	}

	return 0;
}