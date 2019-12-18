#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct coreaudio_data {int /*<<< orphan*/  unit; scalar_t__ default_device; int /*<<< orphan*/  device_id; } ;
typedef  int /*<<< orphan*/  callback_info ;
struct TYPE_6__ {int /*<<< orphan*/ * inputProcRefCon; int /*<<< orphan*/ * inputProc; } ;
struct TYPE_5__ {int /*<<< orphan*/  mSelector; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ AudioObjectPropertyAddress ;
typedef  TYPE_2__ AURenderCallbackStruct ;

/* Variables and functions */
 int /*<<< orphan*/  AudioObjectRemovePropertyListener (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,struct coreaudio_data*) ; 
 int /*<<< orphan*/  PROPERTY_DEFAULT_DEVICE ; 
 int /*<<< orphan*/  PROPERTY_FORMATS ; 
 int /*<<< orphan*/  SCOPE_GLOBAL ; 
 int /*<<< orphan*/  kAudioDevicePropertyDeviceIsAlive ; 
 int /*<<< orphan*/  kAudioObjectPropertyElementMaster ; 
 int /*<<< orphan*/  kAudioObjectPropertyScopeGlobal ; 
 int /*<<< orphan*/  kAudioObjectSystemObject ; 
 int /*<<< orphan*/  kAudioOutputUnitProperty_SetInputCallback ; 
 int /*<<< orphan*/  notification_callback ; 
 int /*<<< orphan*/  set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 

__attribute__((used)) static void coreaudio_remove_hooks(struct coreaudio_data *ca)
{
	AURenderCallbackStruct callback_info = {.inputProc = NULL,
						.inputProcRefCon = NULL};

	AudioObjectPropertyAddress addr = {kAudioDevicePropertyDeviceIsAlive,
					   kAudioObjectPropertyScopeGlobal,
					   kAudioObjectPropertyElementMaster};

	AudioObjectRemovePropertyListener(ca->device_id, &addr,
					  notification_callback, ca);

	addr.mSelector = PROPERTY_FORMATS;
	AudioObjectRemovePropertyListener(ca->device_id, &addr,
					  notification_callback, ca);

	if (ca->default_device) {
		addr.mSelector = PROPERTY_DEFAULT_DEVICE;
		AudioObjectRemovePropertyListener(kAudioObjectSystemObject,
						  &addr, notification_callback,
						  ca);
	}

	set_property(ca->unit, kAudioOutputUnitProperty_SetInputCallback,
		     SCOPE_GLOBAL, 0, &callback_info, sizeof(callback_info));
}