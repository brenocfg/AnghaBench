#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct bss_info* stqe_next; } ;
struct bss_info {scalar_t__ rssi; int /*<<< orphan*/  channel; TYPE_1__ next; } ;
typedef  scalar_t__ int8_t ;
struct TYPE_4__ {int /*<<< orphan*/  softAPchannel; } ;
typedef  scalar_t__ STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 scalar_t__ OK ; 
 int /*<<< orphan*/  enduser_setup_ap_start () ; 
 int /*<<< orphan*/  enduser_setup_check_station_start () ; 
 TYPE_2__* state ; 

__attribute__((used)) static void on_initial_scan_done (void *arg, STATUS status)
{
  ENDUSER_SETUP_DEBUG("on_initial_scan_done");

  if (state == NULL)
  {
    return;
  }

  int8_t rssi = -100;

  if (status == OK)
  {
    /* Find the strongest signal and use the same wi-fi channel for the SoftAP. This is based on an assumption that end-user
     * will likely be choosing that AP to connect to. Since ESP only has one radio, STA and AP must share same channel. This
     * algorithm tries to minimize the SoftAP unavailability when the STA is connecting to verify. If the STA must switch to
     * another wi-fi channel, then the SoftAP will follow it, but the end-user's device will not know that the SoftAP is no
     * longer there until it times out. To mitigate, we try to prevent the need to switch channels, and if a switch does occur,
     * be quick about returning to this channel so that status info can be delivered to the end-user's device before shutting
     * down EUS.
     */
    for (struct bss_info *wn = arg; wn; wn = wn->next.stqe_next)
    {
      if (wn->rssi > rssi)
      {
        state->softAPchannel = wn->channel;
        rssi = wn->rssi;
      }
    }
  }

  enduser_setup_ap_start();
  enduser_setup_check_station_start();
}