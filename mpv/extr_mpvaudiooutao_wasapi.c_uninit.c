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
struct wasapi_state {int /*<<< orphan*/  deviceID; scalar_t__ hAudioThread; scalar_t__ hWake; scalar_t__ hInitDone; } ;
struct ao {struct wasapi_state* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  MP_DBG (struct ao*,char*) ; 
 int /*<<< orphan*/  MP_ERR (struct ao*,char*) ; 
 int /*<<< orphan*/  SAFE_DESTROY (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 int /*<<< orphan*/  WASAPI_THREAD_SHUTDOWN ; 
 scalar_t__ WaitForSingleObject (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_thread_state (struct ao*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wasapi_change_uninit (struct ao*) ; 

__attribute__((used)) static void uninit(struct ao *ao)
{
    MP_DBG(ao, "Uninit wasapi\n");
    struct wasapi_state *state = ao->priv;
    if (state->hWake)
        set_thread_state(ao, WASAPI_THREAD_SHUTDOWN);

    if (state->hAudioThread &&
        WaitForSingleObject(state->hAudioThread, INFINITE) != WAIT_OBJECT_0)
    {
        MP_ERR(ao, "Unexpected return value from WaitForSingleObject "
               "while waiting for audio thread to terminate\n");
    }

    SAFE_DESTROY(state->hInitDone,   CloseHandle(state->hInitDone));
    SAFE_DESTROY(state->hWake,       CloseHandle(state->hWake));
    SAFE_DESTROY(state->hAudioThread,CloseHandle(state->hAudioThread));

    wasapi_change_uninit(ao);

    talloc_free(state->deviceID);

    CoUninitialize();
    MP_DBG(ao, "Uninit wasapi done\n");
}