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
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
typedef  TYPE_1__ mbfl_buffer_converter ;

/* Variables and functions */
 int /*<<< orphan*/  mbfl_memory_device_reset (int /*<<< orphan*/ *) ; 

void
mbfl_buffer_converter_reset(mbfl_buffer_converter *convd)
{
	mbfl_memory_device_reset(&convd->device);
}