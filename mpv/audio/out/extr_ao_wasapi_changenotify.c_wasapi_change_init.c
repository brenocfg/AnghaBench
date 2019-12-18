#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * lpVtbl; } ;
struct change_notify {int is_hotplug; int /*<<< orphan*/  pEnumerator; TYPE_1__ client; int /*<<< orphan*/  monitored; struct ao* ao; } ;
struct wasapi_state {int /*<<< orphan*/  deviceID; struct change_notify change; } ;
struct ao {struct wasapi_state* priv; } ;
typedef  int /*<<< orphan*/  IMMNotificationClient ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_ALL ; 
 int /*<<< orphan*/  CLSID_MMDeviceEnumerator ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  EXIT_ON_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IMMDeviceEnumerator ; 
 int /*<<< orphan*/  IMMDeviceEnumerator_RegisterEndpointNotificationCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_DBG (struct ao*,char*) ; 
 int /*<<< orphan*/  MP_ERR (struct wasapi_state*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_HRESULT_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sIMMNotificationClientVtbl ; 
 int /*<<< orphan*/  wasapi_change_uninit (struct ao*) ; 

HRESULT wasapi_change_init(struct ao *ao, bool is_hotplug)
{
    struct wasapi_state *state = ao->priv;
    struct change_notify *change = &state->change;
    HRESULT hr = CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL,
                                  &IID_IMMDeviceEnumerator,
                                  (void **)&change->pEnumerator);
    EXIT_ON_ERROR(hr);

    // so the callbacks can access the ao
    change->ao = ao;

    // whether or not this is the hotplug instance
    change->is_hotplug = is_hotplug;

    if (is_hotplug) {
        MP_DBG(ao, "Monitoring for hotplug events\n");
    } else {
        // Get the device string to compare with the pwstrDeviceId
        change->monitored = state->deviceID;
        MP_VERBOSE(ao, "Monitoring changes in device %ls\n", change->monitored);
    }

    // COM voodoo to emulate c++ class
    change->client.lpVtbl = &sIMMNotificationClientVtbl;

    // register the change notification client
    hr = IMMDeviceEnumerator_RegisterEndpointNotificationCallback(
        change->pEnumerator, (IMMNotificationClient *)change);
    EXIT_ON_ERROR(hr);

    return hr;
exit_label:
    MP_ERR(state, "Error setting up device change monitoring: %s\n",
           mp_HRESULT_to_str(hr));
    wasapi_change_uninit(ao);
    return hr;
}