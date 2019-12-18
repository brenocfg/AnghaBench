#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {int Event; } ;
typedef  TYPE_1__ SlWlanEvent_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLR_STATUS_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_STATUS_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SL_WLAN_CONNECTION_FAILED_EVENT 134 
#define  SL_WLAN_CONNECT_EVENT 133 
#define  SL_WLAN_DISCONNECT_EVENT 132 
#define  SL_WLAN_P2P_DEV_FOUND_EVENT 131 
#define  SL_WLAN_P2P_NEG_REQ_RECEIVED_EVENT 130 
#define  SL_WLAN_STA_CONNECTED_EVENT 129 
#define  SL_WLAN_STA_DISCONNECTED_EVENT 128 
 int /*<<< orphan*/  STATUS_BIT_CONNECTION ; 
 int /*<<< orphan*/  STATUS_BIT_IP_ACQUIRED ; 
 int /*<<< orphan*/  servers_reset () ; 
 int /*<<< orphan*/  servers_wlan_cycle_power () ; 
 TYPE_2__ wlan_obj ; 

void SimpleLinkWlanEventHandler(SlWlanEvent_t *pWlanEvent) {
    if (!pWlanEvent) {
        return;
    }

    switch(pWlanEvent->Event)
    {
        case SL_WLAN_CONNECT_EVENT:
        {
            //slWlanConnectAsyncResponse_t *pEventData = &pWlanEvent->EventData.STAandP2PModeWlanConnected;
            // copy the new connection data
            //memcpy(wlan_obj.bssid, pEventData->bssid, SL_BSSID_LENGTH);
            //memcpy(wlan_obj.ssid_o, pEventData->ssid_name, pEventData->ssid_len);
            //wlan_obj.ssid_o[pEventData->ssid_len] = '\0';
            SET_STATUS_BIT(wlan_obj.status, STATUS_BIT_CONNECTION);
        #if (MICROPY_PORT_HAS_TELNET || MICROPY_PORT_HAS_FTP)
            // we must reset the servers in case that the last connection
            // was lost without any notification being received
            servers_reset();
        #endif
        }
            break;
        case SL_WLAN_DISCONNECT_EVENT:
            CLR_STATUS_BIT(wlan_obj.status, STATUS_BIT_CONNECTION);
            CLR_STATUS_BIT(wlan_obj.status, STATUS_BIT_IP_ACQUIRED);
        #if (MICROPY_PORT_HAS_TELNET || MICROPY_PORT_HAS_FTP)
            servers_reset();
            servers_wlan_cycle_power();
        #endif
            break;
        case SL_WLAN_STA_CONNECTED_EVENT:
        {
            //slPeerInfoAsyncResponse_t *pEventData = &pWlanEvent->EventData.APModeStaConnected;
            // get the mac address and name of the connected device
            //memcpy(wlan_obj.bssid, pEventData->mac, SL_BSSID_LENGTH);
            //memcpy(wlan_obj.ssid_o, pEventData->go_peer_device_name, pEventData->go_peer_device_name_len);
            //wlan_obj.ssid_o[pEventData->go_peer_device_name_len] = '\0';
            SET_STATUS_BIT(wlan_obj.status, STATUS_BIT_CONNECTION);
        #if (MICROPY_PORT_HAS_TELNET || MICROPY_PORT_HAS_FTP)
            // we must reset the servers in case that the last connection
            // was lost without any notification being received
            servers_reset();
        #endif
        }
            break;
        case SL_WLAN_STA_DISCONNECTED_EVENT:
            CLR_STATUS_BIT(wlan_obj.status, STATUS_BIT_CONNECTION);
        #if (MICROPY_PORT_HAS_TELNET || MICROPY_PORT_HAS_FTP)
            servers_reset();
            servers_wlan_cycle_power();
        #endif
            break;
        case SL_WLAN_P2P_DEV_FOUND_EVENT:
            // TODO
            break;
        case SL_WLAN_P2P_NEG_REQ_RECEIVED_EVENT:
            // TODO
            break;
        case SL_WLAN_CONNECTION_FAILED_EVENT:
            // TODO
            break;
        default:
            break;
    }
}