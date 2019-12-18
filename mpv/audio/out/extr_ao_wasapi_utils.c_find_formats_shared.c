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
struct wasapi_state {int /*<<< orphan*/  pAudioClient; } ;
struct ao {struct wasapi_state* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  Format; } ;
typedef  TYPE_1__ WAVEFORMATEXTENSIBLE ;
typedef  int /*<<< orphan*/  WAVEFORMATEX ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ AUDCLNT_E_UNSUPPORTED_FORMAT ; 
 int /*<<< orphan*/  AUDCLNT_SHAREMODE_SHARED ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXIT_ON_ERROR (scalar_t__) ; 
 scalar_t__ IAudioClient_GetMixFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IAudioClient_IsFormatSupported (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  MP_ERR (struct wasapi_state*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*,int /*<<< orphan*/ ,...) ; 
#define  S_FALSE 129 
#define  S_OK 128 
 int /*<<< orphan*/  mp_HRESULT_to_str (scalar_t__) ; 
 int /*<<< orphan*/  mp_format_res_str (scalar_t__) ; 
 int /*<<< orphan*/  waveformat_copy (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waveformat_to_str (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool find_formats_shared(struct ao *ao, WAVEFORMATEXTENSIBLE *wformat)
{
    struct wasapi_state *state = ao->priv;

    WAVEFORMATEX *closestMatch;
    HRESULT hr = IAudioClient_IsFormatSupported(state->pAudioClient,
                                                AUDCLNT_SHAREMODE_SHARED,
                                                &wformat->Format,
                                                &closestMatch);
    MP_VERBOSE(ao, "Trying %s (shared) -> %s\n",
               waveformat_to_str(&wformat->Format), mp_format_res_str(hr));
    if (hr != AUDCLNT_E_UNSUPPORTED_FORMAT)
        EXIT_ON_ERROR(hr);

    switch (hr) {
    case S_OK:
        break;
    case S_FALSE:
        waveformat_copy(wformat, closestMatch);
        CoTaskMemFree(closestMatch);
        MP_VERBOSE(ao, "Closest match is %s\n",
                   waveformat_to_str(&wformat->Format));
        break;
    default:
        hr = IAudioClient_GetMixFormat(state->pAudioClient, &closestMatch);
        EXIT_ON_ERROR(hr);
        waveformat_copy(wformat, closestMatch);
        MP_VERBOSE(ao, "Fallback to mix format %s\n",
                   waveformat_to_str(&wformat->Format));
        CoTaskMemFree(closestMatch);
    }

    return true;
exit_label:
    MP_ERR(state, "Error finding shared mode format: %s\n",
           mp_HRESULT_to_str(hr));
    return false;
}