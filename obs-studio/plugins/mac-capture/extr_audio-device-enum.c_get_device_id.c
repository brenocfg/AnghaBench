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
struct device_id_data {int found; int /*<<< orphan*/ * id; int /*<<< orphan*/  uid; } ;
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  int /*<<< orphan*/  AudioDeviceID ;

/* Variables and functions */
 scalar_t__ CFStringCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool get_device_id(void *param, CFStringRef cf_name, CFStringRef cf_uid,
			  AudioDeviceID id)
{
	struct device_id_data *data = param;

	if (CFStringCompare(cf_uid, data->uid, 0) == 0) {
		*data->id = id;
		data->found = true;
		return false;
	}

	UNUSED_PARAMETER(cf_name);
	return true;
}