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
struct wasapi_state {int /*<<< orphan*/  log; } ;
struct ao {int /*<<< orphan*/  log; struct wasapi_state* priv; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  COINIT_MULTITHREADED ; 
 int /*<<< orphan*/  CoInitializeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXIT_ON_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_DBG (struct ao*,char*) ; 
 int /*<<< orphan*/  MP_FATAL (struct wasapi_state*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hotplug_uninit (struct ao*) ; 
 int /*<<< orphan*/  mp_HRESULT_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wasapi_change_init (struct ao*,int) ; 

__attribute__((used)) static int hotplug_init(struct ao *ao)
{
    MP_DBG(ao, "Hotplug init\n");
    struct wasapi_state *state = ao->priv;
    state->log = ao->log;
    CoInitializeEx(NULL, COINIT_MULTITHREADED);
    HRESULT hr = wasapi_change_init(ao, true);
    EXIT_ON_ERROR(hr);

    return 0;
    exit_label:
    MP_FATAL(state, "Error setting up audio hotplug: %s\n", mp_HRESULT_to_str(hr));
    hotplug_uninit(ao);
    return -1;
}