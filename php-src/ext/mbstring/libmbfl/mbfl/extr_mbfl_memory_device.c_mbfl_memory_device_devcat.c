#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pos; scalar_t__ buffer; } ;
typedef  TYPE_1__ mbfl_memory_device ;

/* Variables and functions */
 int mbfl_memory_device_strncat (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 

int
mbfl_memory_device_devcat(mbfl_memory_device *dest, mbfl_memory_device *src)
{
	return mbfl_memory_device_strncat(dest, (const char *) src->buffer, src->pos);
}