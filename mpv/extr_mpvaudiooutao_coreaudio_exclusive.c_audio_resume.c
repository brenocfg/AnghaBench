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
struct priv {int /*<<< orphan*/  render_cb; int /*<<< orphan*/  device; } ;
struct ao {struct priv* priv; } ;
typedef  int /*<<< orphan*/  OSStatus ;

/* Variables and functions */
 int /*<<< orphan*/  AudioDeviceStart (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_CA_WARN (char*) ; 

__attribute__((used)) static void audio_resume(struct ao *ao)
{
    struct priv *p = ao->priv;

    OSStatus err = AudioDeviceStart(p->device, p->render_cb);
    CHECK_CA_WARN("can't start audio device");
}