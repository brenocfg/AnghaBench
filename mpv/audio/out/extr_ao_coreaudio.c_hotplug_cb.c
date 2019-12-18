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
struct ao {int dummy; } ;
typedef  int /*<<< orphan*/  UInt32 ;
typedef  int /*<<< orphan*/  OSStatus ;
typedef  int /*<<< orphan*/  AudioObjectPropertyAddress ;
typedef  int /*<<< orphan*/  AudioObjectID ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*) ; 
 int /*<<< orphan*/  ao_hotplug_event (struct ao*) ; 
 int /*<<< orphan*/  noErr ; 
 int /*<<< orphan*/  reinit_device (struct ao*) ; 

__attribute__((used)) static OSStatus hotplug_cb(AudioObjectID id, UInt32 naddr,
                           const AudioObjectPropertyAddress addr[],
                           void *ctx)
{
    struct ao *ao = ctx;
    MP_VERBOSE(ao, "Handling potential hotplug event...\n");
    reinit_device(ao);
    ao_hotplug_event(ao);
    return noErr;
}