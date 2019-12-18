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
struct coreaudio_data {char* device_name; int /*<<< orphan*/  device_id; } ;
typedef  int UInt32 ;
struct TYPE_3__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ OSStatus ;
typedef  int /*<<< orphan*/ * CFStringRef ;
typedef  TYPE_1__ AudioObjectPropertyAddress ;

/* Variables and functions */
 scalar_t__ AudioObjectGetPropertyData (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 char* cfstr_copy_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kAudioDevicePropertyDeviceNameCFString ; 
 int /*<<< orphan*/  kAudioObjectPropertyElementMaster ; 
 int /*<<< orphan*/  kAudioObjectPropertyScopeInput ; 
 int /*<<< orphan*/  kCFStringEncodingUTF8 ; 
 scalar_t__ noErr ; 

__attribute__((used)) static bool coreaudio_get_device_name(struct coreaudio_data *ca)
{
	CFStringRef cf_name = NULL;
	UInt32 size = sizeof(CFStringRef);
	char *name = NULL;

	const AudioObjectPropertyAddress addr = {
		kAudioDevicePropertyDeviceNameCFString,
		kAudioObjectPropertyScopeInput,
		kAudioObjectPropertyElementMaster};

	OSStatus stat = AudioObjectGetPropertyData(ca->device_id, &addr, 0,
						   NULL, &size, &cf_name);
	if (stat != noErr) {
		blog(LOG_WARNING,
		     "[coreaudio_get_device_name] failed to "
		     "get name: %d",
		     (int)stat);
		return false;
	}

	name = cfstr_copy_cstr(cf_name, kCFStringEncodingUTF8);
	if (!name) {
		blog(LOG_WARNING, "[coreaudio_get_device_name] failed to "
				  "convert name to cstr for some reason");
		return false;
	}

	bfree(ca->device_name);
	ca->device_name = name;

	if (cf_name)
		CFRelease(cf_name);

	return true;
}