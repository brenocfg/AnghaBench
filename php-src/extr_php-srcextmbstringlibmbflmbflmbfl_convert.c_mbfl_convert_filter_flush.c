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
struct TYPE_4__ {int (* flush_function ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; int /*<<< orphan*/  (* filter_flush ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int stub2 (int /*<<< orphan*/ ) ; 

int
mbfl_convert_filter_flush(mbfl_convert_filter *filter)
{
	(*filter->filter_flush)(filter);
	return (filter->flush_function ? (*filter->flush_function)(filter->data) : 0);
}