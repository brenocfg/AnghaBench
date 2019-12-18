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

/* Variables and functions */
 int /*<<< orphan*/  mbfl_free (void*) ; 
 int /*<<< orphan*/  mbfl_identify_filter_cleanup (int /*<<< orphan*/ *) ; 

void mbfl_identify_filter_delete(mbfl_identify_filter *filter)
{
	if (filter == NULL) {
		return;
	}

	mbfl_identify_filter_cleanup(filter);
	mbfl_free((void*)filter);
}