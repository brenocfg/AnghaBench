#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int trace_flags; int wifi_scan_state; int (* wifi_scan_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int wifi_join_state; int pend_rejoin; int pend_rejoin_wpa; int pend_disassoc; int /*<<< orphan*/  wifi_scan_env; } ;
typedef  TYPE_2__ cyw43_t ;
struct TYPE_8__ {int /*<<< orphan*/  scan_result; } ;
struct TYPE_10__ {scalar_t__ event_type; int status; int reason; int flags; int /*<<< orphan*/  interface; TYPE_1__ u; } ;
typedef  TYPE_3__ cyw43_async_event_t ;

/* Variables and functions */
 scalar_t__ CYW43_EV_AUTH ; 
 scalar_t__ CYW43_EV_DEAUTH_IND ; 
 scalar_t__ CYW43_EV_DISASSOC ; 
 scalar_t__ CYW43_EV_ESCAN_RESULT ; 
 scalar_t__ CYW43_EV_LINK ; 
 scalar_t__ CYW43_EV_PRUNE ; 
 scalar_t__ CYW43_EV_PSK_SUP ; 
 scalar_t__ CYW43_EV_SET_SSID ; 
 int /*<<< orphan*/  CYW43_ITF_STA ; 
 int CYW43_TRACE_ASYNC_EV ; 
 int /*<<< orphan*/  PENDSV_DISPATCH_CYW43 ; 
 int WIFI_JOIN_STATE_ACTIVE ; 
 int WIFI_JOIN_STATE_ALL ; 
 int WIFI_JOIN_STATE_AUTH ; 
 void* WIFI_JOIN_STATE_BADAUTH ; 
 int WIFI_JOIN_STATE_FAIL ; 
 int WIFI_JOIN_STATE_KEYED ; 
 int WIFI_JOIN_STATE_LINK ; 
 int WIFI_JOIN_STATE_NONET ; 
 int /*<<< orphan*/  cyw43_dump_async_event (TYPE_3__ const*) ; 
 int /*<<< orphan*/  cyw43_poll_func ; 
 int /*<<< orphan*/  cyw43_tcpip_set_link_down (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cyw43_tcpip_set_link_up (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pendsv_schedule_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void cyw43_cb_process_async_event(void *cb_data, const cyw43_async_event_t *ev) {
    cyw43_t *self = cb_data;

    if (self->trace_flags & CYW43_TRACE_ASYNC_EV) {
        cyw43_dump_async_event(ev);
    }

    if (ev->event_type == CYW43_EV_ESCAN_RESULT && self->wifi_scan_state == 1) {
        // Escan result event
        if (ev->status == 8) {
            // Partial result
            int ret = self->wifi_scan_cb(self->wifi_scan_env, &ev->u.scan_result);
            if (ret != 0) {
                // TODO need to abort scan, or just ignore any more results
            }
        } else if (ev->status == 0) {
            // Scan complete
            self->wifi_scan_state = 2;
        }

    } else if (ev->event_type == CYW43_EV_DISASSOC) {
        cyw43_tcpip_set_link_down(self, CYW43_ITF_STA);
        self->wifi_join_state = 0x0000;

    /*
    } else if (ev->event_type == CYW43_EV_DISASSOC_IND) {
        if (ev->interface == CYW43_ITF_AP) {
            // Station disassociated with our AP, let DHCP server know so it can free the IP address
            dhcp_server_disassoc(&self->dhcp_server, buf + 24);
        }
    */

    // WiFi join events
    } else if (ev->event_type == CYW43_EV_PRUNE) {
        if (ev->status == 0 && ev->reason == 8) {
            // RSN mismatch, retry join with WPA auth
            self->pend_rejoin = true;
            self->pend_rejoin_wpa = true;
            pendsv_schedule_dispatch(PENDSV_DISPATCH_CYW43, cyw43_poll_func);
        }
    } else if (ev->event_type == CYW43_EV_SET_SSID) {
        if (ev->status == 0) {
            // Success setting SSID
        } else if (ev->status == 3 && ev->reason == 0) {
            self->wifi_join_state = WIFI_JOIN_STATE_NONET;
            // No matching SSID found (could be out of range, or down)
        } else {
            // Other failure setting SSID
            self->wifi_join_state = WIFI_JOIN_STATE_FAIL;
        }
    } else if (ev->event_type == CYW43_EV_AUTH) {
        if (ev->status == 0) {
            self->wifi_join_state |= WIFI_JOIN_STATE_AUTH;
        } else if (ev->status == 6) {
            // Unsolicited auth packet, ignore it
        } else {
            // Cannot authenticate
            self->wifi_join_state = WIFI_JOIN_STATE_BADAUTH;
        }
    } else if (ev->event_type == CYW43_EV_DEAUTH_IND) {
        if (ev->status == 0 && ev->reason == 2) {
            // Deauth, probably because password was wrong; disassociate
            self->pend_disassoc = true;
            pendsv_schedule_dispatch(PENDSV_DISPATCH_CYW43, cyw43_poll_func);
        }
    } else if (ev->event_type == CYW43_EV_LINK) {
        if (ev->status == 0) {
            if (ev->flags & 1) {
                // Link is up
                if (ev->interface == CYW43_ITF_STA) {
                    self->wifi_join_state |= WIFI_JOIN_STATE_LINK;
                } else {
                    cyw43_tcpip_set_link_up(self, ev->interface);
                }
            } else {
                // Link is down
                cyw43_tcpip_set_link_down(self, ev->interface);
            }
        }
    } else if (ev->event_type == CYW43_EV_PSK_SUP) {
        if (ev->status == 6) { // WLC_SUP_KEYED
            self->wifi_join_state |= WIFI_JOIN_STATE_KEYED;
        } else if ((ev->status == 4 || ev->status == 8 || ev->status == 11) && ev->reason == 15) {
            // Timeout waiting for key exchange M1/M3/G1
            // Probably at edge of the cell, retry
            self->pend_rejoin = true;
            pendsv_schedule_dispatch(PENDSV_DISPATCH_CYW43, cyw43_poll_func);
        } else {
            // PSK_SUP failure
            self->wifi_join_state = WIFI_JOIN_STATE_BADAUTH;
        }
    }

    if (self->wifi_join_state == WIFI_JOIN_STATE_ALL) {
        // STA connected
        self->wifi_join_state = WIFI_JOIN_STATE_ACTIVE;
        cyw43_tcpip_set_link_up(self, CYW43_ITF_STA);
    }
}