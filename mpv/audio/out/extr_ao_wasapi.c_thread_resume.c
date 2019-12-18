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
struct wasapi_state {int /*<<< orphan*/  pAudioClient; } ;
struct ao {struct wasapi_state* priv; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAudioClient_Start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_DBG (struct wasapi_state*,char*) ; 
 int /*<<< orphan*/  MP_ERR (struct wasapi_state*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_HRESULT_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_feed (struct ao*) ; 
 int /*<<< orphan*/  thread_reset (struct ao*) ; 

__attribute__((used)) static void thread_resume(struct ao *ao)
{
    struct wasapi_state *state = ao->priv;
    MP_DBG(state, "Thread Resume\n");
    thread_reset(ao);
    thread_feed(ao);

    HRESULT hr = IAudioClient_Start(state->pAudioClient);
    if (FAILED(hr)) {
        MP_ERR(state, "IAudioClient_Start returned %s\n",
               mp_HRESULT_to_str(hr));
    }
}