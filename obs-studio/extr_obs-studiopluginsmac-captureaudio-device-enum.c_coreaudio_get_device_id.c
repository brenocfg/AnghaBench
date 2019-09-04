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
struct device_id_data {int member_2; int found; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  int /*<<< orphan*/  AudioDeviceID ;

/* Variables and functions */
 int /*<<< orphan*/  enum_devices (int /*<<< orphan*/ ,struct device_id_data*) ; 
 int /*<<< orphan*/  get_device_id ; 

bool coreaudio_get_device_id(CFStringRef uid, AudioDeviceID *id)
{
	struct device_id_data data = {uid, id, false};
	enum_devices(get_device_id, &data);
	return data.found;
}