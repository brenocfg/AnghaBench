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
typedef  int /*<<< orphan*/  mbfl_identify_filter ;
typedef  int /*<<< orphan*/  mbfl_encoding ;

/* Variables and functions */
 int /*<<< orphan*/  mbfl_free (int /*<<< orphan*/ *) ; 
 scalar_t__ mbfl_identify_filter_init2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ mbfl_malloc (int) ; 

mbfl_identify_filter *mbfl_identify_filter_new2(const mbfl_encoding *encoding)
{
	mbfl_identify_filter *filter;

	/* allocate */
	filter = (mbfl_identify_filter *)mbfl_malloc(sizeof(mbfl_identify_filter));
	if (filter == NULL) {
		return NULL;
	}

	if (mbfl_identify_filter_init2(filter, encoding)) {
		mbfl_free(filter);
		return NULL;
	}

	return filter;
}