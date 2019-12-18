#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char uint8_t ;
typedef  int /*<<< orphan*/  ucPower ;
typedef  scalar_t__ int8_t ;
typedef  unsigned char _u8 ;
typedef  void* _u32 ;
struct TYPE_4__ {void* FilterIdMask; } ;
typedef  TYPE_1__ _WlanRxFilterOperationCommandBuff_t ;
struct TYPE_6__ {int lease_time; void* ipv4_addr_last; void* ipv4_addr_start; } ;
struct TYPE_5__ {void* ipV4DnsServer; void* ipV4Gateway; void* ipV4Mask; void* ipV4; } ;
typedef  TYPE_2__ SlNetCfgIpV4Args_t ;
typedef  TYPE_3__ SlNetAppDhcpServerBasicOpt_t ;
typedef  int /*<<< orphan*/  RxFilterIdMask ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_ON_ERROR (int /*<<< orphan*/ ) ; 
 int IPCONFIG_MODE_ENABLE_IPV4 ; 
 int /*<<< orphan*/  NETAPP_SET_DHCP_SRV_BASIC_OPT ; 
 scalar_t__ ROLE_AP ; 
 int /*<<< orphan*/  SL_CONNECTION_POLICY (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SL_IPV4_AP_P2P_GO_STATIC_ENABLE ; 
 int /*<<< orphan*/  SL_IPV4_STA_P2P_CL_DHCP_ENABLE ; 
 void* SL_IPV4_VAL (int,int,int,int) ; 
 int /*<<< orphan*/  SL_NET_APP_DHCP_SERVER_ID ; 
 int /*<<< orphan*/  SL_NET_APP_HTTP_SERVER_ID ; 
 int /*<<< orphan*/  SL_NORMAL_POLICY ; 
 int /*<<< orphan*/  SL_POLICY_CONNECTION ; 
 int /*<<< orphan*/  SL_POLICY_PM ; 
 int /*<<< orphan*/  SL_REMOVE_RX_FILTER ; 
 int /*<<< orphan*/  SL_WLAN_CFG_GENERAL_PARAM_ID ; 
 int /*<<< orphan*/  WLAN_GENERAL_PARAM_OPT_AP_TX_POWER ; 
 int /*<<< orphan*/  WLAN_GENERAL_PARAM_OPT_COUNTRY_CODE ; 
 int /*<<< orphan*/  WLAN_GENERAL_PARAM_OPT_STA_TX_POWER ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 
 int /*<<< orphan*/  pyb_rtc_get_seconds () ; 
 int /*<<< orphan*/  sl_NetAppMDNSUnRegisterService (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl_NetAppSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int /*<<< orphan*/  sl_NetAppStart (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl_NetAppStop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl_NetCfgSet (int /*<<< orphan*/ ,int,int,unsigned char*) ; 
 int /*<<< orphan*/  sl_WlanPolicySet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl_WlanProfileDel (int) ; 
 int /*<<< orphan*/  sl_WlanRxFilterSet (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  sl_WlanSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int /*<<< orphan*/  wlan_first_start () ; 
 int /*<<< orphan*/  wlan_reenable (scalar_t__) ; 
 int /*<<< orphan*/  wlan_servers_start () ; 
 int /*<<< orphan*/  wlan_servers_stop () ; 
 int /*<<< orphan*/  wlan_set_antenna (unsigned char) ; 
 int /*<<< orphan*/  wlan_set_channel (unsigned char) ; 
 int /*<<< orphan*/  wlan_set_current_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlan_set_mode (scalar_t__) ; 
 int /*<<< orphan*/  wlan_set_security (unsigned char,char const*,unsigned char) ; 
 int /*<<< orphan*/  wlan_set_ssid (char const*,unsigned char,int) ; 
 int /*<<< orphan*/  wlan_sl_disconnect () ; 

void wlan_sl_init (int8_t mode, const char *ssid, uint8_t ssid_len, uint8_t auth, const char *key, uint8_t key_len,
                   uint8_t channel, uint8_t antenna, bool add_mac) {

    // stop the servers
    wlan_servers_stop();

    // do a basic start
    wlan_first_start();

    // close any active connections
    wlan_sl_disconnect();

    // Remove all profiles
    ASSERT_ON_ERROR(sl_WlanProfileDel(0xFF));

    // Enable the DHCP client
    uint8_t value = 1;
    ASSERT_ON_ERROR(sl_NetCfgSet(SL_IPV4_STA_P2P_CL_DHCP_ENABLE, 1, 1, &value));

    // Set PM policy to normal
    ASSERT_ON_ERROR(sl_WlanPolicySet(SL_POLICY_PM, SL_NORMAL_POLICY, NULL, 0));

    // Unregister mDNS services
    ASSERT_ON_ERROR(sl_NetAppMDNSUnRegisterService(0, 0));

    // Stop the internal HTTP server
    sl_NetAppStop(SL_NET_APP_HTTP_SERVER_ID);

    // Remove all 64 filters (8 * 8)
    _WlanRxFilterOperationCommandBuff_t  RxFilterIdMask;
    memset ((void *)&RxFilterIdMask, 0 ,sizeof(RxFilterIdMask));
    memset(RxFilterIdMask.FilterIdMask, 0xFF, 8);
    ASSERT_ON_ERROR(sl_WlanRxFilterSet(SL_REMOVE_RX_FILTER, (_u8 *)&RxFilterIdMask, sizeof(_WlanRxFilterOperationCommandBuff_t)));

#if MICROPY_HW_ANTENNA_DIVERSITY
    // set the antenna type
    wlan_set_antenna (antenna);
#endif

    // switch to the requested mode
    wlan_set_mode(mode);

    // stop and start again (we need to in the propper mode from now on)
    wlan_reenable(mode);

    // Set Tx power level for station or AP mode
    // Number between 0-15, as dB offset from max power - 0 will set max power
    uint8_t ucPower = 0;
    if (mode == ROLE_AP) {
        ASSERT_ON_ERROR(sl_WlanSet(SL_WLAN_CFG_GENERAL_PARAM_ID, WLAN_GENERAL_PARAM_OPT_AP_TX_POWER, sizeof(ucPower),
                                   (unsigned char *)&ucPower));

        // configure all parameters
        wlan_set_ssid (ssid, ssid_len, add_mac);
        wlan_set_security (auth, key, key_len);
        wlan_set_channel (channel);

        // set the country
        _u8*  country = (_u8*)"EU";
        ASSERT_ON_ERROR(sl_WlanSet(SL_WLAN_CFG_GENERAL_PARAM_ID, WLAN_GENERAL_PARAM_OPT_COUNTRY_CODE, 2, country));

        SlNetCfgIpV4Args_t ipV4;
        ipV4.ipV4          = (_u32)SL_IPV4_VAL(192,168,1,1);            // _u32 IP address
        ipV4.ipV4Mask      = (_u32)SL_IPV4_VAL(255,255,255,0);          // _u32 Subnet mask for this AP
        ipV4.ipV4Gateway   = (_u32)SL_IPV4_VAL(192,168,1,1);            // _u32 Default gateway address
        ipV4.ipV4DnsServer = (_u32)SL_IPV4_VAL(192,168,1,1);            // _u32 DNS server address
        ASSERT_ON_ERROR(sl_NetCfgSet(SL_IPV4_AP_P2P_GO_STATIC_ENABLE, IPCONFIG_MODE_ENABLE_IPV4,
                                     sizeof(SlNetCfgIpV4Args_t), (_u8 *)&ipV4));

        SlNetAppDhcpServerBasicOpt_t dhcpParams;
        dhcpParams.lease_time      =  4096;                             // lease time (in seconds) of the IP Address
        dhcpParams.ipv4_addr_start =  SL_IPV4_VAL(192,168,1,2);         // first IP Address for allocation.
        dhcpParams.ipv4_addr_last  =  SL_IPV4_VAL(192,168,1,254);       // last IP Address for allocation.
        ASSERT_ON_ERROR(sl_NetAppStop(SL_NET_APP_DHCP_SERVER_ID));      // Stop DHCP server before settings
        ASSERT_ON_ERROR(sl_NetAppSet(SL_NET_APP_DHCP_SERVER_ID, NETAPP_SET_DHCP_SRV_BASIC_OPT,
                                     sizeof(SlNetAppDhcpServerBasicOpt_t), (_u8* )&dhcpParams));  // set parameters
        ASSERT_ON_ERROR(sl_NetAppStart(SL_NET_APP_DHCP_SERVER_ID));     // Start DHCP server with new settings

        // stop and start again
        wlan_reenable(mode);
    } else { // STA and P2P modes
        ASSERT_ON_ERROR(sl_WlanSet(SL_WLAN_CFG_GENERAL_PARAM_ID, WLAN_GENERAL_PARAM_OPT_STA_TX_POWER,
                                   sizeof(ucPower), (unsigned char *)&ucPower));
        // set connection policy to Auto + Fast (tries to connect to the last connected AP)
        ASSERT_ON_ERROR(sl_WlanPolicySet(SL_POLICY_CONNECTION, SL_CONNECTION_POLICY(1, 1, 0, 0, 0), NULL, 0));
    }

    // set current time and date (needed to validate certificates)
    wlan_set_current_time (pyb_rtc_get_seconds());

    // start the servers before returning
    wlan_servers_start();
}