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
struct TYPE_3__ {int /*<<< orphan*/ * filter2; int /*<<< orphan*/ * filter1; } ;
typedef  TYPE_1__ mbfl_buffer_converter ;

/* Variables and functions */
 int /*<<< orphan*/  mbfl_convert_filter_flush (int /*<<< orphan*/ *) ; 

int
mbfl_buffer_converter_flush(mbfl_buffer_converter *convd)
{
	if (convd == NULL) {
		return -1;
	}

	if (convd->filter1 != NULL) {
		mbfl_convert_filter_flush(convd->filter1);
	}
	if (convd->filter2 != NULL) {
		mbfl_convert_filter_flush(convd->filter2);
	}

	return 0;
}