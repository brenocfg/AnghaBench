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
struct TYPE_6__ {int /*<<< orphan*/  (* filter_copy ) (TYPE_1__*,TYPE_1__*) ;} ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,TYPE_1__*) ; 

void
mbfl_convert_filter_copy(
    mbfl_convert_filter *src,
    mbfl_convert_filter *dest)
{
	if (src->filter_copy != NULL) {
		src->filter_copy(src, dest);
		return;
	}

	*dest = *src;
}