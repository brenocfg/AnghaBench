#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  encoding; } ;
typedef  TYPE_1__ mbfl_string ;
struct TYPE_9__ {int /*<<< orphan*/  device; int /*<<< orphan*/  to; } ;
typedef  TYPE_2__ mbfl_buffer_converter ;

/* Variables and functions */
 TYPE_1__* mbfl_memory_device_result (int /*<<< orphan*/ *,TYPE_1__*) ; 

mbfl_string *
mbfl_buffer_converter_result(mbfl_buffer_converter *convd, mbfl_string *result)
{
	if (convd == NULL || result == NULL) {
		return NULL;
	}
	result->encoding = convd->to;
	return mbfl_memory_device_result(&convd->device, result);
}