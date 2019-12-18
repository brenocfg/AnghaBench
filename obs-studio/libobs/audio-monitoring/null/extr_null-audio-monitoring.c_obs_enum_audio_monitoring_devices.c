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
typedef  void* obs_enum_audio_device_cb ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 

void obs_enum_audio_monitoring_devices(obs_enum_audio_device_cb cb, void *data)
{
	UNUSED_PARAMETER(cb);
	UNUSED_PARAMETER(data);
}