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
typedef  int /*<<< orphan*/  wchar_t ;
struct wasapi_state {scalar_t__ share_mode; int /*<<< orphan*/  pSessionControl; } ;
struct ao {struct wasapi_state* priv; } ;
typedef  enum aocontrol { ____Placeholder_aocontrol } aocontrol ;

/* Variables and functions */
#define  AOCONTROL_UPDATE_STREAM_TITLE 128 
 scalar_t__ AUDCLNT_SHAREMODE_EXCLUSIVE ; 
 int CONTROL_FALSE ; 
 int CONTROL_OK ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioSessionControl_GetDisplayName (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IAudioSessionControl_SetDisplayName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SAFE_DESTROY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mp_from_utf8 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ *) ; 
 int thread_control_exclusive (struct ao*,int,void*) ; 
 int thread_control_shared (struct ao*,int,void*) ; 
 int /*<<< orphan*/  wcscmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int thread_control(struct ao *ao, enum aocontrol cmd, void *arg)
{
    struct wasapi_state *state = ao->priv;

    // common to exclusive and shared
    switch (cmd) {
    case AOCONTROL_UPDATE_STREAM_TITLE:
        if (!state->pSessionControl)
            return CONTROL_FALSE;

        wchar_t *title = mp_from_utf8(NULL, (char*)arg);
        wchar_t *tmp = NULL;
        // There is a weird race condition in the IAudioSessionControl itself --
        // it seems that *sometimes* the SetDisplayName does not take effect and
        // it still shows the old title. Use this loop to insist until it works.
        do {
            IAudioSessionControl_SetDisplayName(state->pSessionControl, title, NULL);

            SAFE_DESTROY(tmp, CoTaskMemFree(tmp));
            IAudioSessionControl_GetDisplayName(state->pSessionControl, &tmp);
        } while (wcscmp(title, tmp));
        SAFE_DESTROY(tmp, CoTaskMemFree(tmp));
        talloc_free(title);
        return CONTROL_OK;
    }

    return state->share_mode == AUDCLNT_SHAREMODE_EXCLUSIVE ?
        thread_control_exclusive(ao, cmd, arg) :
        thread_control_shared(ao, cmd, arg);
}