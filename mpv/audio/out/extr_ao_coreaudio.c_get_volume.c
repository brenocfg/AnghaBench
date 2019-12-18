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
struct priv {int /*<<< orphan*/  audio_unit; } ;
struct ao_control_vol {float left; float right; } ;
struct ao {struct priv* priv; } ;
typedef  int /*<<< orphan*/  OSStatus ;

/* Variables and functions */
 int /*<<< orphan*/  AudioUnitGetParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  CHECK_CA_ERROR (char*) ; 
 int CONTROL_ERROR ; 
 int CONTROL_TRUE ; 
 int /*<<< orphan*/  kAudioUnitScope_Global ; 
 int /*<<< orphan*/  kHALOutputParam_Volume ; 

__attribute__((used)) static int get_volume(struct ao *ao, struct ao_control_vol *vol) {
    struct priv *p = ao->priv;
    float auvol;
    OSStatus err =
        AudioUnitGetParameter(p->audio_unit, kHALOutputParam_Volume,
                              kAudioUnitScope_Global, 0, &auvol);

    CHECK_CA_ERROR("could not get HAL output volume");
    vol->left = vol->right = auvol * 100.0;
    return CONTROL_TRUE;
coreaudio_error:
    return CONTROL_ERROR;
}