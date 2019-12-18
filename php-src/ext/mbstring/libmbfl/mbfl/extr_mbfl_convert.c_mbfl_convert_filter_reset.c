#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mbfl_convert_vtbl {int dummy; } ;
typedef  int /*<<< orphan*/  mbfl_encoding ;
struct TYPE_5__ {int /*<<< orphan*/  data; int /*<<< orphan*/  flush_function; int /*<<< orphan*/  output_function; int /*<<< orphan*/  (* filter_dtor ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  mbfl_convert_filter_common_init (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,struct mbfl_convert_vtbl const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mbfl_convert_vtbl* mbfl_convert_filter_get_vtbl (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 struct mbfl_convert_vtbl vtbl_pass ; 

void mbfl_convert_filter_reset(mbfl_convert_filter *filter,
	    const mbfl_encoding *from, const mbfl_encoding *to)
{
	const struct mbfl_convert_vtbl *vtbl;

	/* destruct old filter */
	(*filter->filter_dtor)(filter);

	vtbl = mbfl_convert_filter_get_vtbl(from, to);

	if (vtbl == NULL) {
		vtbl = &vtbl_pass;
	}

	mbfl_convert_filter_common_init(filter, from, to, vtbl,
			filter->output_function, filter->flush_function, filter->data);
}