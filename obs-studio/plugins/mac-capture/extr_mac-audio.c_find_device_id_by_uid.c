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
struct coreaudio_data {int default_device; int no_devices; int /*<<< orphan*/  device_id; scalar_t__ device_uid; scalar_t__ input; } ;
typedef  int UInt32 ;
struct TYPE_3__ {int /*<<< orphan*/  mSelector; int /*<<< orphan*/  mElement; int /*<<< orphan*/  mScope; } ;
typedef  scalar_t__ OSStatus ;
typedef  int /*<<< orphan*/ * CFStringRef ;
typedef  TYPE_1__ AudioObjectPropertyAddress ;
typedef  int /*<<< orphan*/  AudioDeviceID ;

/* Variables and functions */
 scalar_t__ AudioObjectGetPropertyData (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CFStringCreateWithCString (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROPERTY_DEFAULT_DEVICE ; 
 scalar_t__ astrcmpi (scalar_t__,char*) ; 
 scalar_t__ bstrdup (char*) ; 
 int coreaudio_get_device_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_default_output_device (struct coreaudio_data*) ; 
 int /*<<< orphan*/  kAudioObjectPropertyElementMaster ; 
 int /*<<< orphan*/  kAudioObjectPropertyScopeGlobal ; 
 int /*<<< orphan*/  kAudioObjectSystemObject ; 
 int /*<<< orphan*/  kCFStringEncodingUTF8 ; 
 scalar_t__ noErr ; 

__attribute__((used)) static bool find_device_id_by_uid(struct coreaudio_data *ca)
{
	UInt32 size = sizeof(AudioDeviceID);
	CFStringRef cf_uid = NULL;
	CFStringRef qual = NULL;
	UInt32 qual_size = 0;
	OSStatus stat;
	bool success;

	AudioObjectPropertyAddress addr = {
		.mScope = kAudioObjectPropertyScopeGlobal,
		.mElement = kAudioObjectPropertyElementMaster};

	if (!ca->device_uid)
		ca->device_uid = bstrdup("default");

	ca->default_device = false;
	ca->no_devices = false;

	/* have to do this because mac output devices don't actually exist */
	if (astrcmpi(ca->device_uid, "default") == 0) {
		if (ca->input) {
			ca->default_device = true;
		} else {
			if (!get_default_output_device(ca)) {
				ca->no_devices = true;
				return false;
			}
		}
	}

	cf_uid = CFStringCreateWithCString(NULL, ca->device_uid,
					   kCFStringEncodingUTF8);

	if (ca->default_device) {
		addr.mSelector = PROPERTY_DEFAULT_DEVICE;
		stat = AudioObjectGetPropertyData(kAudioObjectSystemObject,
						  &addr, qual_size, &qual,
						  &size, &ca->device_id);
		success = (stat == noErr);
	} else {
		success = coreaudio_get_device_id(cf_uid, &ca->device_id);
	}

	if (cf_uid)
		CFRelease(cf_uid);

	return success;
}