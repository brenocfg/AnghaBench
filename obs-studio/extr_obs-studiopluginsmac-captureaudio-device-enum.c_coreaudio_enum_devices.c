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
struct device_list {int dummy; } ;
struct add_data {int member_1; struct device_list* member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  coreaudio_enum_add_device ; 
 int /*<<< orphan*/  enum_devices (int /*<<< orphan*/ ,struct add_data*) ; 

void coreaudio_enum_devices(struct device_list *list, bool input)
{
	struct add_data data = {list, input};
	enum_devices(coreaudio_enum_add_device, &data);
}