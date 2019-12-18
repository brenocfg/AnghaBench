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
struct mbfl_convert_vtbl {int /*<<< orphan*/  filter_copy; int /*<<< orphan*/  filter_flush; int /*<<< orphan*/  filter_function; int /*<<< orphan*/  filter_dtor; int /*<<< orphan*/  (* filter_ctor ) (TYPE_1__*) ;} ;
typedef  int /*<<< orphan*/  mbfl_encoding ;
struct TYPE_4__ {int (* output_function ) (int,void*) ;int (* flush_function ) (void*) ;int illegal_substchar; int /*<<< orphan*/  (* filter_ctor ) (TYPE_1__*) ;int /*<<< orphan*/  filter_copy; int /*<<< orphan*/  filter_flush; int /*<<< orphan*/  filter_function; int /*<<< orphan*/  filter_dtor; scalar_t__ num_illegalchar; int /*<<< orphan*/  illegal_mode; void* data; int /*<<< orphan*/  const* to; int /*<<< orphan*/  const* from; } ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  MBFL_OUTPUTFILTER_ILLEGAL_MODE_CHAR ; 
 int mbfl_filter_output_null (int,void*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static int
mbfl_convert_filter_common_init(
	mbfl_convert_filter *filter,
	const mbfl_encoding *from,
	const mbfl_encoding *to,
	const struct mbfl_convert_vtbl *vtbl,
    int (*output_function)(int, void* ),
    int (*flush_function)(void*),
    void* data)
{
	/* encoding structure */
	filter->from = from;
	filter->to = to;

	if (output_function != NULL) {
		filter->output_function = output_function;
	} else {
		filter->output_function = mbfl_filter_output_null;
	}

	filter->flush_function = flush_function;
	filter->data = data;
	filter->illegal_mode = MBFL_OUTPUTFILTER_ILLEGAL_MODE_CHAR;
	filter->illegal_substchar = 0x3f;		/* '?' */
	filter->num_illegalchar = 0;
	filter->filter_ctor = vtbl->filter_ctor;
	filter->filter_dtor = vtbl->filter_dtor;
	filter->filter_function = vtbl->filter_function;
	filter->filter_flush = vtbl->filter_flush;
	filter->filter_copy = vtbl->filter_copy;

	(*filter->filter_ctor)(filter);

	return 0;
}