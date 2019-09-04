#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ mFormatID; } ;
struct priv {TYPE_1__ original_asbd; int /*<<< orphan*/  original_asbd_stream; int /*<<< orphan*/  audio_unit; } ;
struct ao {struct priv* priv; } ;
typedef  int /*<<< orphan*/  OSStatus ;

/* Variables and functions */
 int /*<<< orphan*/  AudioComponentInstanceDispose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AudioOutputUnitStop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AudioUnitUninitialize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CA_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CHECK_CA_WARN (char*) ; 
 int /*<<< orphan*/  kAudioStreamPropertyPhysicalFormat ; 

__attribute__((used)) static void uninit(struct ao *ao)
{
    struct priv *p = ao->priv;
    AudioOutputUnitStop(p->audio_unit);
    AudioUnitUninitialize(p->audio_unit);
    AudioComponentInstanceDispose(p->audio_unit);

    if (p->original_asbd.mFormatID) {
        OSStatus err = CA_SET(p->original_asbd_stream,
                              kAudioStreamPropertyPhysicalFormat,
                              &p->original_asbd);
        CHECK_CA_WARN("could not restore physical stream format");
    }
}