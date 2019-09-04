#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  encoding; } ;
typedef  TYPE_1__ mbfl_string ;
struct TYPE_12__ {int /*<<< orphan*/  device; int /*<<< orphan*/  to; int /*<<< orphan*/ * filter2; int /*<<< orphan*/ * filter1; } ;
typedef  TYPE_2__ mbfl_buffer_converter ;

/* Variables and functions */
 int /*<<< orphan*/  mbfl_buffer_converter_feed (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mbfl_convert_filter_flush (int /*<<< orphan*/ *) ; 
 TYPE_1__* mbfl_memory_device_result (int /*<<< orphan*/ *,TYPE_1__*) ; 

mbfl_string *
mbfl_buffer_converter_feed_result(mbfl_buffer_converter *convd, mbfl_string *string,
				  mbfl_string *result)
{
	if (convd == NULL || string == NULL || result == NULL) {
		return NULL;
	}
	mbfl_buffer_converter_feed(convd, string);
	if (convd->filter1 != NULL) {
		mbfl_convert_filter_flush(convd->filter1);
	}
	if (convd->filter2 != NULL) {
		mbfl_convert_filter_flush(convd->filter2);
	}
	result->encoding = convd->to;
	return mbfl_memory_device_result(&convd->device, result);
}