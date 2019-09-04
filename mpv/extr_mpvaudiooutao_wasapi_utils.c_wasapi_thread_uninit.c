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
struct wasapi_state {int /*<<< orphan*/  hTask; scalar_t__ pDevice; scalar_t__ pAudioClient; scalar_t__ pSessionControl; scalar_t__ pEndpointVolume; scalar_t__ pAudioVolume; scalar_t__ pAudioClock; scalar_t__ pRenderClient; } ;
struct ao {struct wasapi_state* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  AvRevertMmThreadCharacteristics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAudioClient_Stop (scalar_t__) ; 
 int /*<<< orphan*/  MP_DBG (struct ao*,char*) ; 
 int /*<<< orphan*/  SAFE_DESTROY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAFE_RELEASE (scalar_t__) ; 

void wasapi_thread_uninit(struct ao *ao)
{
    struct wasapi_state *state = ao->priv;
    MP_DBG(ao, "Thread shutdown\n");

    if (state->pAudioClient)
        IAudioClient_Stop(state->pAudioClient);

    SAFE_RELEASE(state->pRenderClient);
    SAFE_RELEASE(state->pAudioClock);
    SAFE_RELEASE(state->pAudioVolume);
    SAFE_RELEASE(state->pEndpointVolume);
    SAFE_RELEASE(state->pSessionControl);
    SAFE_RELEASE(state->pAudioClient);
    SAFE_RELEASE(state->pDevice);
#if !HAVE_UWP
    SAFE_DESTROY(state->hTask, AvRevertMmThreadCharacteristics(state->hTask));
#endif
    MP_DBG(ao, "Thread uninit done\n");
}