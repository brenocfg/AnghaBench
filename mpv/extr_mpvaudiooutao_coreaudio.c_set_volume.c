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
struct ao_control_vol {double left; double right; } ;
struct ao {struct priv* priv; } ;
typedef  int /*<<< orphan*/  OSStatus ;

/* Variables and functions */
 int /*<<< orphan*/  AudioUnitSetParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_CA_ERROR (char*) ; 
 int CONTROL_ERROR ; 
 int CONTROL_TRUE ; 
 int /*<<< orphan*/  kAudioUnitScope_Global ; 
 int /*<<< orphan*/  kHALOutputParam_Volume ; 

__attribute__((used)) static int set_volume(struct ao *ao, struct ao_control_vol *vol) {
    struct priv *p = ao->priv;
    float auvol = (vol->left + vol->right) / 200.0;
    OSStatus err =
        AudioUnitSetParameter(p->audio_unit, kHALOutputParam_Volume,
                              kAudioUnitScope_Global, 0, auvol, 0);
    CHECK_CA_ERROR("could not set HAL output volume");
    return CONTROL_TRUE;
coreaudio_error:
    return CONTROL_ERROR;
}