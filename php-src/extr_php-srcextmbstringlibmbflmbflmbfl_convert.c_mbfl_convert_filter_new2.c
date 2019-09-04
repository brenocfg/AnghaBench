#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mbfl_convert_vtbl {int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;
typedef  int /*<<< orphan*/  mbfl_encoding ;
typedef  int /*<<< orphan*/  mbfl_convert_filter ;

/* Variables and functions */
 scalar_t__ mbfl_convert_filter_common_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,struct mbfl_convert_vtbl const*,int (*) (int,void*),int (*) (void*),void*) ; 
 int /*<<< orphan*/  mbfl_free (int /*<<< orphan*/ *) ; 
 scalar_t__ mbfl_malloc (int) ; 
 int /*<<< orphan*/ * mbfl_no2encoding (int /*<<< orphan*/ ) ; 
 struct mbfl_convert_vtbl vtbl_pass ; 

mbfl_convert_filter *
mbfl_convert_filter_new2(
	const struct mbfl_convert_vtbl *vtbl,
    int (*output_function)(int, void* ),
    int (*flush_function)(void*),
    void* data)
{
	mbfl_convert_filter * filter;
	const mbfl_encoding *from_encoding, *to_encoding;

	if (vtbl == NULL) {
		vtbl = &vtbl_pass;
	}

	from_encoding = mbfl_no2encoding(vtbl->from);
	to_encoding = mbfl_no2encoding(vtbl->to);

	/* allocate */
	filter = (mbfl_convert_filter *)mbfl_malloc(sizeof(mbfl_convert_filter));
	if (filter == NULL) {
		return NULL;
	}

	if (mbfl_convert_filter_common_init(filter, from_encoding, to_encoding, vtbl,
			output_function, flush_function, data)) {
		mbfl_free(filter);
		return NULL;
	}

	return filter;
}