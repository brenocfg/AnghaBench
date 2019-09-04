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
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* output_function ) (int,int /*<<< orphan*/ ) ;scalar_t__ cache; scalar_t__ status; } ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  CK (int /*<<< orphan*/ ) ; 
 int MBFL_WCSGROUP_MASK ; 
 int MBFL_WCSGROUP_THROUGH ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

int mbfl_filt_put_invalid_char(int c, mbfl_convert_filter *filter)
{
	int w;
	w = c & MBFL_WCSGROUP_MASK;
	w |= MBFL_WCSGROUP_THROUGH;
	filter->status = 0;
	filter->cache = 0;
	CK((*filter->output_function)(w, filter->data));
	return 0;
}