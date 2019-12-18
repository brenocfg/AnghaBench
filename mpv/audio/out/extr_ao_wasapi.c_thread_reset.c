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
struct wasapi_state {int /*<<< orphan*/  sample_count; int /*<<< orphan*/  pAudioClient; } ;
struct ao {struct wasapi_state* priv; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAudioClient_Reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAudioClient_Stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_DBG (struct wasapi_state*,char*) ; 
 int /*<<< orphan*/  MP_ERR (struct wasapi_state*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_HRESULT_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void thread_reset(struct ao *ao)
{
    struct wasapi_state *state = ao->priv;
    HRESULT hr;
    MP_DBG(state, "Thread Reset\n");
    hr = IAudioClient_Stop(state->pAudioClient);
    if (FAILED(hr))
        MP_ERR(state, "IAudioClient_Stop returned: %s\n", mp_HRESULT_to_str(hr));

    hr = IAudioClient_Reset(state->pAudioClient);
    if (FAILED(hr))
        MP_ERR(state, "IAudioClient_Reset returned: %s\n", mp_HRESULT_to_str(hr));

    atomic_store(&state->sample_count, 0);
}