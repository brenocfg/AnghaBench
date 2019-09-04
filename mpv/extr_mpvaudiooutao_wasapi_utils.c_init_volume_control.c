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
struct wasapi_state {scalar_t__ share_mode; int /*<<< orphan*/  pAudioVolume; int /*<<< orphan*/  pEndpointVolume; scalar_t__ vol_hw_support; int /*<<< orphan*/  pAudioClient; int /*<<< orphan*/  pDevice; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ AUDCLNT_SHAREMODE_EXCLUSIVE ; 
 int /*<<< orphan*/  CLSCTX_ALL ; 
 int /*<<< orphan*/  EXIT_ON_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAudioClient_GetService (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IAudioEndpointVolume_QueryHardwareSupport (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  IID_IAudioEndpointVolume ; 
 int /*<<< orphan*/  IID_ISimpleAudioVolume ; 
 int /*<<< orphan*/  IMMDeviceActivator_Activate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  MP_DBG (struct wasapi_state*,char*) ; 
 int /*<<< orphan*/  MP_WARN (struct wasapi_state*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAFE_RELEASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_HRESULT_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_volume_control(struct wasapi_state *state)
{
    HRESULT hr;
    if (state->share_mode == AUDCLNT_SHAREMODE_EXCLUSIVE) {
        MP_DBG(state, "Activating pEndpointVolume interface\n");
        hr = IMMDeviceActivator_Activate(state->pDevice,
                                         &IID_IAudioEndpointVolume,
                                         CLSCTX_ALL, NULL,
                                         (void **)&state->pEndpointVolume);
        EXIT_ON_ERROR(hr);

        MP_DBG(state, "IAudioEndpointVolume::QueryHardwareSupport\n");
        hr = IAudioEndpointVolume_QueryHardwareSupport(state->pEndpointVolume,
                                                       &state->vol_hw_support);
        EXIT_ON_ERROR(hr);
    } else {
        MP_DBG(state, "IAudioClient::Initialize pAudioVolume\n");
        hr = IAudioClient_GetService(state->pAudioClient,
                                     &IID_ISimpleAudioVolume,
                                     (void **)&state->pAudioVolume);
        EXIT_ON_ERROR(hr);
    }
    return;
exit_label:
    state->vol_hw_support = 0;
    SAFE_RELEASE(state->pEndpointVolume);
    SAFE_RELEASE(state->pAudioVolume);
    MP_WARN(state, "Error setting up volume control: %s\n",
            mp_HRESULT_to_str(hr));
}