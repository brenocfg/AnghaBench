#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wasapi_state {int /*<<< orphan*/  pAudioClient; } ;
struct ao {struct wasapi_state* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  Format; } ;
typedef  TYPE_1__ WAVEFORMATEXTENSIBLE ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  AUDCLNT_SHAREMODE_EXCLUSIVE ; 
 int /*<<< orphan*/  IAudioClient_IsFormatSupported (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_format_res_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waveformat_to_str (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool try_format_exclusive(struct ao *ao, WAVEFORMATEXTENSIBLE *wformat)
{
    struct wasapi_state *state = ao->priv;
    HRESULT hr = IAudioClient_IsFormatSupported(state->pAudioClient,
                                                AUDCLNT_SHAREMODE_EXCLUSIVE,
                                                &wformat->Format, NULL);
    MP_VERBOSE(ao, "Trying %s (exclusive) -> %s\n",
               waveformat_to_str(&wformat->Format), mp_format_res_str(hr));
    return SUCCEEDED(hr);
}