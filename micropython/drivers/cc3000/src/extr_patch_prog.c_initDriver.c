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

/* Variables and functions */
 int /*<<< orphan*/  CC3000_UsynchCallback ; 
 int HCI_EVNT_WLAN_ASYNC_PING_REPORT ; 
 int HCI_EVNT_WLAN_KEEPALIVE ; 
 int HCI_EVNT_WLAN_UNSOL_INIT ; 
 int /*<<< orphan*/  ReadWlanInterruptPin ; 
 int /*<<< orphan*/  SpiPauseSpi ; 
 int /*<<< orphan*/  SpiResumeSpi ; 
 int /*<<< orphan*/  WriteWlanPin ; 
 scalar_t__ aucCC3000_prefix ; 
 int /*<<< orphan*/  sendBootLoaderPatch ; 
 int /*<<< orphan*/  sendDriverPatch ; 
 int /*<<< orphan*/  sendWLFWPatch ; 
 int /*<<< orphan*/  systick_sleep (int) ; 
 int /*<<< orphan*/  wlan_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlan_ioctl_del_profile (int) ; 
 int /*<<< orphan*/  wlan_ioctl_set_connection_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlan_set_event_mask (int) ; 
 int /*<<< orphan*/  wlan_smart_config_set_prefix (char*) ; 
 int /*<<< orphan*/  wlan_start (unsigned short) ; 

__attribute__((used)) static int initDriver(unsigned short cRequestPatch)
{
    // WLAN On API Implementation
    wlan_init(CC3000_UsynchCallback, sendWLFWPatch, sendDriverPatch, sendBootLoaderPatch,
              ReadWlanInterruptPin, SpiResumeSpi, SpiPauseSpi, WriteWlanPin);

    // Trigger a WLAN device
    wlan_start(cRequestPatch);
    wlan_smart_config_set_prefix((char*)aucCC3000_prefix);
    wlan_ioctl_set_connection_policy(0, 0, 0);
    wlan_ioctl_del_profile(255);

    // Mask out all non-required events from CC3000
    wlan_set_event_mask(HCI_EVNT_WLAN_KEEPALIVE|
                        HCI_EVNT_WLAN_UNSOL_INIT|
                        HCI_EVNT_WLAN_ASYNC_PING_REPORT);

    //unsolicicted_events_timer_init();
    systick_sleep(100);
    return(0);
}