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
typedef  int /*<<< orphan*/  uint32_t ;
struct priv {int /*<<< orphan*/  device; } ;
struct ao {struct priv* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  mSelector; int /*<<< orphan*/  mElement; int /*<<< orphan*/  mScope; } ;
typedef  scalar_t__ OSStatus ;
typedef  TYPE_1__ AudioObjectPropertyAddress ;
typedef  int /*<<< orphan*/  AudioDeviceID ;

/* Variables and functions */
 scalar_t__ AudioObjectAddPropertyListener (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,struct ao*) ; 
 scalar_t__ AudioObjectRemovePropertyListener (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,struct ao*) ; 
 int MP_ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kAudioDevicePropertyDeviceHasChanged ; 
 int /*<<< orphan*/  kAudioHardwarePropertyDevices ; 
 int /*<<< orphan*/  kAudioObjectPropertyElementMaster ; 
 int /*<<< orphan*/  kAudioObjectPropertyScopeGlobal ; 
 int /*<<< orphan*/  kAudioObjectSystemObject ; 
 scalar_t__ noErr ; 
 int /*<<< orphan*/  property_listener_cb ; 

__attribute__((used)) static OSStatus enable_property_listener(struct ao *ao, bool enabled)
{
    struct priv *p = ao->priv;

    uint32_t selectors[] = {kAudioDevicePropertyDeviceHasChanged,
                            kAudioHardwarePropertyDevices};
    AudioDeviceID devs[] = {p->device,
                            kAudioObjectSystemObject};
    assert(MP_ARRAY_SIZE(selectors) == MP_ARRAY_SIZE(devs));

    OSStatus status = noErr;
    for (int n = 0; n < MP_ARRAY_SIZE(devs); n++) {
        AudioObjectPropertyAddress addr = {
            .mScope    = kAudioObjectPropertyScopeGlobal,
            .mElement  = kAudioObjectPropertyElementMaster,
            .mSelector = selectors[n],
        };
        AudioDeviceID device = devs[n];

        OSStatus status2;
        if (enabled) {
            status2 = AudioObjectAddPropertyListener(
                device, &addr, property_listener_cb, ao);
        } else {
            status2 = AudioObjectRemovePropertyListener(
                device, &addr, property_listener_cb, ao);
        }
        if (status == noErr)
            status = status2;
    }

    return status;
}