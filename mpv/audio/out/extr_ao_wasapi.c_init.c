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
struct wasapi_state {int opt_exclusive; int init_ok; void* hInitDone; int /*<<< orphan*/  hAudioThread; int /*<<< orphan*/  dispatch; void* hWake; scalar_t__ deviceID; int /*<<< orphan*/  log; } ;
struct ao {int init_flags; int /*<<< orphan*/  probing; int /*<<< orphan*/  log; struct wasapi_state* priv; } ;

/* Variables and functions */
 int AO_INIT_EXCLUSIVE ; 
 int /*<<< orphan*/  AudioThread ; 
 int /*<<< orphan*/  COINIT_MULTITHREADED ; 
 int /*<<< orphan*/  CloseHandle (void*) ; 
 int /*<<< orphan*/  CoInitializeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ao*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  MP_DBG (struct ao*,char*) ; 
 int /*<<< orphan*/  MP_FATAL (struct ao*,char*) ; 
 int /*<<< orphan*/  SAFE_DESTROY (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitForSingleObject (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_dispatch_create (struct wasapi_state*) ; 
 int /*<<< orphan*/  mp_dispatch_set_wakeup_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ao*) ; 
 int /*<<< orphan*/  thread_wakeup ; 
 int /*<<< orphan*/  uninit (struct ao*) ; 
 int /*<<< orphan*/  wasapi_change_init (struct ao*,int) ; 
 scalar_t__ wasapi_find_deviceID (struct ao*) ; 

__attribute__((used)) static int init(struct ao *ao)
{
    MP_DBG(ao, "Init wasapi\n");
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    struct wasapi_state *state = ao->priv;
    state->log = ao->log;

    state->opt_exclusive |= ao->init_flags & AO_INIT_EXCLUSIVE;

#if !HAVE_UWP
    state->deviceID = wasapi_find_deviceID(ao);
    if (!state->deviceID) {
        uninit(ao);
        return -1;
    }
#endif

    if (state->deviceID)
        wasapi_change_init(ao, false);

    state->hInitDone = CreateEventW(NULL, FALSE, FALSE, NULL);
    state->hWake     = CreateEventW(NULL, FALSE, FALSE, NULL);
    if (!state->hInitDone || !state->hWake) {
        MP_FATAL(ao, "Error creating events\n");
        uninit(ao);
        return -1;
    }

    state->dispatch = mp_dispatch_create(state);
    mp_dispatch_set_wakeup_fn(state->dispatch, thread_wakeup, ao);

    state->init_ok = false;
    state->hAudioThread = CreateThread(NULL, 0, &AudioThread, ao, 0, NULL);
    if (!state->hAudioThread) {
        MP_FATAL(ao, "Failed to create audio thread\n");
        uninit(ao);
        return -1;
    }

    WaitForSingleObject(state->hInitDone, INFINITE); // wait on init complete
    SAFE_DESTROY(state->hInitDone,CloseHandle(state->hInitDone));
    if (!state->init_ok) {
        if (!ao->probing)
            MP_FATAL(ao, "Received failure from audio thread\n");
        uninit(ao);
        return -1;
    }

    MP_DBG(ao, "Init wasapi done\n");
    return 0;
}