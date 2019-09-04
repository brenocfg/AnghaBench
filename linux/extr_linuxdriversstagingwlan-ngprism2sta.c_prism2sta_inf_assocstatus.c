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
struct wlandevice {int /*<<< orphan*/  netdev; struct hfa384x* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  assocstatus; } ;
struct hfa384x_inf_frame {TYPE_1__ info; } ;
struct hfa384x_assoc_status {scalar_t__ assocstatus; scalar_t__ reason; int /*<<< orphan*/  sta_addr; } ;
struct TYPE_4__ {int cnt; int* assoc; int /*<<< orphan*/ * addr; } ;
struct hfa384x {TYPE_2__ authlist; } ;
typedef  int /*<<< orphan*/  rec ;

/* Variables and functions */
 scalar_t__ HFA384x_ASSOCSTATUS_AUTHFAIL ; 
 scalar_t__ HFA384x_ASSOCSTATUS_REASSOC ; 
 scalar_t__ HFA384x_ASSOCSTATUS_STAASSOC ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpus (scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (struct hfa384x_assoc_status*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void prism2sta_inf_assocstatus(struct wlandevice *wlandev,
				      struct hfa384x_inf_frame *inf)
{
	struct hfa384x *hw = wlandev->priv;
	struct hfa384x_assoc_status rec;
	int i;

	memcpy(&rec, &inf->info.assocstatus, sizeof(rec));
	le16_to_cpus(&rec.assocstatus);
	le16_to_cpus(&rec.reason);

	/*
	 * Find the address in the list of authenticated stations.
	 * If it wasn't found, then this address has not been previously
	 * authenticated and something weird has happened if this is
	 * anything other than an "authentication failed" message.
	 * If the address was found, then set the "associated" flag for
	 * that station, based on whether the station is associating or
	 * losing its association.  Something weird has also happened
	 * if we find the address in the list of authenticated stations
	 * but we are getting an "authentication failed" message.
	 */

	for (i = 0; i < hw->authlist.cnt; i++)
		if (ether_addr_equal(rec.sta_addr, hw->authlist.addr[i]))
			break;

	if (i >= hw->authlist.cnt) {
		if (rec.assocstatus != HFA384x_ASSOCSTATUS_AUTHFAIL)
			netdev_warn(wlandev->netdev,
				    "assocstatus info frame received for non-authenticated station.\n");
	} else {
		hw->authlist.assoc[i] =
		    (rec.assocstatus == HFA384x_ASSOCSTATUS_STAASSOC ||
		     rec.assocstatus == HFA384x_ASSOCSTATUS_REASSOC);

		if (rec.assocstatus == HFA384x_ASSOCSTATUS_AUTHFAIL)
			netdev_warn(wlandev->netdev,
				    "authfail assocstatus info frame received for authenticated station.\n");
	}
}