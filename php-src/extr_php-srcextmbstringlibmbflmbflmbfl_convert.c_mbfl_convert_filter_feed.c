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
struct TYPE_4__ {int (* filter_function ) (int,TYPE_1__*) ;} ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int stub1 (int,TYPE_1__*) ; 

int
mbfl_convert_filter_feed(int c, mbfl_convert_filter *filter)
{
	return (*filter->filter_function)(c, filter);
}