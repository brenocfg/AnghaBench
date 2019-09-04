#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * val; int /*<<< orphan*/  encoding; } ;
typedef  TYPE_2__ mbfl_string ;
struct TYPE_7__ {int /*<<< orphan*/  pos; int /*<<< orphan*/ * buffer; } ;
struct TYPE_9__ {TYPE_1__ device; int /*<<< orphan*/  to; } ;
typedef  TYPE_3__ mbfl_buffer_converter ;

/* Variables and functions */

mbfl_string *
mbfl_buffer_converter_getbuffer(mbfl_buffer_converter *convd, mbfl_string *result)
{
	if (convd != NULL && result != NULL && convd->device.buffer != NULL) {
		result->encoding = convd->to;
		result->val = convd->device.buffer;
		result->len = convd->device.pos;
	} else {
		result = NULL;
	}

	return result;
}