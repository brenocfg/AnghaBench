#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* array; int /*<<< orphan*/  num; } ;
struct device_list {TYPE_3__ items; } ;
struct coreaudio_data {int /*<<< orphan*/  device_uid; } ;
struct TYPE_4__ {int /*<<< orphan*/  array; } ;
struct TYPE_5__ {TYPE_1__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coreaudio_enum_devices (struct device_list*,int) ; 
 int /*<<< orphan*/  device_list_free (struct device_list*) ; 
 int /*<<< orphan*/  memset (struct device_list*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool get_default_output_device(struct coreaudio_data *ca)
{
	struct device_list list;

	memset(&list, 0, sizeof(struct device_list));
	coreaudio_enum_devices(&list, false);

	if (!list.items.num)
		return false;

	bfree(ca->device_uid);
	ca->device_uid = bstrdup(list.items.array[0].value.array);

	device_list_free(&list);
	return true;
}