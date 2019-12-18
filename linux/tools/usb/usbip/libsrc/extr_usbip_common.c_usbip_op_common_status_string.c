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
struct TYPE_2__ {char const* desc; int num; } ;

/* Variables and functions */
 TYPE_1__* op_common_status_strings ; 

const char *usbip_op_common_status_string(int status)
{
	for (int i = 0; op_common_status_strings[i].desc != NULL; i++)
		if (op_common_status_strings[i].num == status)
			return op_common_status_strings[i].desc;

	return "Unknown Op Common Status";
}