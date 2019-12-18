#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  id ;
typedef  int UInt32 ;
struct TYPE_3__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  OSStatus ;
typedef  TYPE_1__ AudioObjectPropertyAddress ;
typedef  int /*<<< orphan*/  AudioDeviceID ;

/* Variables and functions */
 int /*<<< orphan*/  AudioObjectGetPropertyData (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alloc_default_id ; 
 char* bzalloc (int) ; 
 int /*<<< orphan*/  kAudioHardwarePropertyDefaultSystemOutputDevice ; 
 int /*<<< orphan*/  kAudioObjectPropertyElementMaster ; 
 int /*<<< orphan*/  kAudioObjectPropertyScopeGlobal ; 
 int /*<<< orphan*/  kAudioObjectSystemObject ; 
 int /*<<< orphan*/  obs_enum_audio_monitoring_device (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ,int) ; 
 scalar_t__ success (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void get_default_id(char **p_id)
{
	AudioObjectPropertyAddress addr = {
		kAudioHardwarePropertyDefaultSystemOutputDevice,
		kAudioObjectPropertyScopeGlobal,
		kAudioObjectPropertyElementMaster};

	if (*p_id)
		return;

	OSStatus stat;
	AudioDeviceID id = 0;
	UInt32 size = sizeof(id);

	stat = AudioObjectGetPropertyData(kAudioObjectSystemObject, &addr, 0,
					  NULL, &size, &id);
	if (success(stat, "AudioObjectGetPropertyData"))
		obs_enum_audio_monitoring_device(alloc_default_id, p_id, id,
						 true);
	if (!*p_id)
		*p_id = bzalloc(1);
}