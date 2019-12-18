#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  enum_device_proc_t ;
typedef  int UInt32 ;
struct TYPE_4__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  OSStatus ;
typedef  TYPE_1__ AudioObjectPropertyAddress ;
typedef  int /*<<< orphan*/  AudioDeviceID ;

/* Variables and functions */
 int /*<<< orphan*/  AudioObjectGetPropertyData (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AudioObjectGetPropertyDataSize (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bmalloc (int) ; 
 int /*<<< orphan*/  coreaudio_enum_device (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ enum_success (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kAudioHardwarePropertyDevices ; 
 int /*<<< orphan*/  kAudioObjectPropertyElementMaster ; 
 int /*<<< orphan*/  kAudioObjectPropertyScopeGlobal ; 
 int /*<<< orphan*/  kAudioObjectSystemObject ; 

__attribute__((used)) static void enum_devices(enum_device_proc_t proc, void *param)
{
	AudioObjectPropertyAddress addr = {kAudioHardwarePropertyDevices,
					   kAudioObjectPropertyScopeGlobal,
					   kAudioObjectPropertyElementMaster};

	UInt32 size = 0;
	UInt32 count;
	OSStatus stat;
	AudioDeviceID *ids;

	stat = AudioObjectGetPropertyDataSize(kAudioObjectSystemObject, &addr,
					      0, NULL, &size);
	if (!enum_success(stat, "get kAudioObjectSystemObject data size"))
		return;

	ids = bmalloc(size);
	count = size / sizeof(AudioDeviceID);

	stat = AudioObjectGetPropertyData(kAudioObjectSystemObject, &addr, 0,
					  NULL, &size, ids);

	if (enum_success(stat, "get kAudioObjectSystemObject data"))
		for (UInt32 i = 0; i < count; i++)
			if (!coreaudio_enum_device(proc, param, ids[i]))
				break;

	bfree(ids);
}