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
typedef  int (* enum_device_proc_t ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
typedef  int UInt32 ;
struct TYPE_4__ {int /*<<< orphan*/  mSelector; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  OSStatus ;
typedef  int /*<<< orphan*/ * CFStringRef ;
typedef  TYPE_1__ AudioObjectPropertyAddress ;
typedef  int /*<<< orphan*/  AudioDeviceID ;

/* Variables and functions */
 int /*<<< orphan*/  AudioObjectGetPropertyData (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  AudioObjectGetPropertyDataSize (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enum_success (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kAudioDevicePropertyDeviceNameCFString ; 
 int /*<<< orphan*/  kAudioDevicePropertyDeviceUID ; 
 int /*<<< orphan*/  kAudioDevicePropertyScopeInput ; 
 int /*<<< orphan*/  kAudioDevicePropertyStreams ; 
 int /*<<< orphan*/  kAudioObjectPropertyElementMaster ; 

__attribute__((used)) static bool coreaudio_enum_device(enum_device_proc_t proc, void *param,
				  AudioDeviceID id)
{
	UInt32 size = 0;
	CFStringRef cf_name = NULL;
	CFStringRef cf_uid = NULL;
	bool enum_next = true;
	OSStatus stat;

	AudioObjectPropertyAddress addr = {kAudioDevicePropertyStreams,
					   kAudioDevicePropertyScopeInput,
					   kAudioObjectPropertyElementMaster};

	/* check to see if it's a mac input device */
	AudioObjectGetPropertyDataSize(id, &addr, 0, NULL, &size);
	if (!size)
		return true;

	size = sizeof(CFStringRef);

	addr.mSelector = kAudioDevicePropertyDeviceUID;
	stat = AudioObjectGetPropertyData(id, &addr, 0, NULL, &size, &cf_uid);
	if (!enum_success(stat, "get audio device UID"))
		return true;

	addr.mSelector = kAudioDevicePropertyDeviceNameCFString;
	stat = AudioObjectGetPropertyData(id, &addr, 0, NULL, &size, &cf_name);
	if (!enum_success(stat, "get audio device name"))
		goto fail;

	enum_next = proc(param, cf_name, cf_uid, id);

fail:
	if (cf_name)
		CFRelease(cf_name);
	if (cf_uid)
		CFRelease(cf_uid);
	return enum_next;
}