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
struct tep_handle {int test_filters; } ;

/* Variables and functions */

void tep_set_test_filters(struct tep_handle *tep, int test_filters)
{
	if (tep)
		tep->test_filters = test_filters;
}