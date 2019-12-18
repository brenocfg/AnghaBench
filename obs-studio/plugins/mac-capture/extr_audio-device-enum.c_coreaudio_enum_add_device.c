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
struct TYPE_2__ {int /*<<< orphan*/  array; } ;
struct device_item {TYPE_1__ value; TYPE_1__ name; } ;
struct add_data {int /*<<< orphan*/  list; scalar_t__ input; } ;
typedef  int /*<<< orphan*/  item ;
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  int /*<<< orphan*/  AudioDeviceID ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfstr_copy_dstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  device_is_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_item_free (struct device_item*) ; 
 int /*<<< orphan*/  device_list_add (int /*<<< orphan*/ ,struct device_item*) ; 
 int /*<<< orphan*/  kCFStringEncodingUTF8 ; 
 int /*<<< orphan*/  memset (struct device_item*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool coreaudio_enum_add_device(void *param, CFStringRef cf_name,
				      CFStringRef cf_uid, AudioDeviceID id)
{
	struct add_data *data = param;
	struct device_item item;

	memset(&item, 0, sizeof(item));

	if (!cfstr_copy_dstr(cf_name, kCFStringEncodingUTF8, &item.name))
		goto fail;
	if (!cfstr_copy_dstr(cf_uid, kCFStringEncodingUTF8, &item.value))
		goto fail;

	if (data->input || !device_is_input(item.value.array))
		device_list_add(data->list, &item);

fail:
	device_item_free(&item);

	UNUSED_PARAMETER(id);
	return true;
}