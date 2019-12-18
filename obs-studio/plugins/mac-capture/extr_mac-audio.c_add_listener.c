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
struct coreaudio_data {int /*<<< orphan*/  device_id; } ;
typedef  int /*<<< orphan*/  UInt32 ;
struct TYPE_3__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  OSStatus ;
typedef  TYPE_1__ AudioObjectPropertyAddress ;

/* Variables and functions */
 int /*<<< orphan*/  AudioObjectAddPropertyListener (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,struct coreaudio_data*) ; 
 int /*<<< orphan*/  kAudioObjectPropertyElementMaster ; 
 int /*<<< orphan*/  kAudioObjectPropertyScopeGlobal ; 
 int /*<<< orphan*/  notification_callback ; 

__attribute__((used)) static OSStatus add_listener(struct coreaudio_data *ca, UInt32 property)
{
	AudioObjectPropertyAddress addr = {property,
					   kAudioObjectPropertyScopeGlobal,
					   kAudioObjectPropertyElementMaster};

	return AudioObjectAddPropertyListener(ca->device_id, &addr,
					      notification_callback, ca);
}