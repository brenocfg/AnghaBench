#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {char const* desc; scalar_t__ num; } ;

/* Variables and functions */
 TYPE_1__* portst_strings ; 

const char *usbip_status_string(int32_t status)
{
	for (int i = 0; portst_strings[i].desc != NULL; i++)
		if (portst_strings[i].num == status)
			return portst_strings[i].desc;

	return "Unknown Status";
}