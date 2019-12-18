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
struct priv {int /*<<< orphan*/  hog_pid; int /*<<< orphan*/  device; int /*<<< orphan*/  changed_mixing; int /*<<< orphan*/  original_asbd; int /*<<< orphan*/  stream; int /*<<< orphan*/  render_cb; } ;
struct ao {struct priv* priv; } ;
typedef  int /*<<< orphan*/  OSStatus ;

/* Variables and functions */
 int /*<<< orphan*/  AudioDeviceDestroyIOProcID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AudioDeviceStop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_CA_WARN (char*) ; 
 int /*<<< orphan*/  MP_WARN (struct ao*,char*) ; 
 int /*<<< orphan*/  ca_change_physical_format_sync (struct ao*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ca_enable_mixing (struct ao*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ca_unlock_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_property_listener (struct ao*,int) ; 
 int /*<<< orphan*/  noErr ; 

__attribute__((used)) static void uninit(struct ao *ao)
{
    struct priv *p = ao->priv;
    OSStatus err = noErr;

    err = enable_property_listener(ao, false);
    CHECK_CA_WARN("can't remove device listener, this may cause a crash");

    err = AudioDeviceStop(p->device, p->render_cb);
    CHECK_CA_WARN("failed to stop audio device");

    err = AudioDeviceDestroyIOProcID(p->device, p->render_cb);
    CHECK_CA_WARN("failed to remove device render callback");

    if (!ca_change_physical_format_sync(ao, p->stream, p->original_asbd))
        MP_WARN(ao, "can't revert to original device format\n");

    err = ca_enable_mixing(ao, p->device, p->changed_mixing);
    CHECK_CA_WARN("can't re-enable mixing");

    err = ca_unlock_device(p->device, &p->hog_pid);
    CHECK_CA_WARN("can't release hog mode");
}