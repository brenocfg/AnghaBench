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
struct wlandevice {int /*<<< orphan*/  netdev; } ;
struct hfa384x_inf_frame {int infotype; } ;

/* Variables and functions */
#define  HFA384x_IT_ASSOCREQ 139 
#define  HFA384x_IT_ASSOCSTATUS 138 
#define  HFA384x_IT_AUTHREQ 137 
#define  HFA384x_IT_CHINFORESULTS 136 
#define  HFA384x_IT_COMMTALLIES 135 
#define  HFA384x_IT_HANDOVERADDR 134 
#define  HFA384x_IT_HOSTSCANRESULTS 133 
#define  HFA384x_IT_KEYIDCHANGED 132 
#define  HFA384x_IT_LINKSTATUS 131 
#define  HFA384x_IT_MICFAILURE 130 
#define  HFA384x_IT_PSUSERCNT 129 
#define  HFA384x_IT_SCANRESULTS 128 
 int /*<<< orphan*/  le16_to_cpus (int*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  prism2sta_inf_assocstatus (struct wlandevice*,struct hfa384x_inf_frame*) ; 
 int /*<<< orphan*/  prism2sta_inf_authreq (struct wlandevice*,struct hfa384x_inf_frame*) ; 
 int /*<<< orphan*/  prism2sta_inf_chinforesults (struct wlandevice*,struct hfa384x_inf_frame*) ; 
 int /*<<< orphan*/  prism2sta_inf_handover (struct wlandevice*,struct hfa384x_inf_frame*) ; 
 int /*<<< orphan*/  prism2sta_inf_hostscanresults (struct wlandevice*,struct hfa384x_inf_frame*) ; 
 int /*<<< orphan*/  prism2sta_inf_linkstatus (struct wlandevice*,struct hfa384x_inf_frame*) ; 
 int /*<<< orphan*/  prism2sta_inf_psusercnt (struct wlandevice*,struct hfa384x_inf_frame*) ; 
 int /*<<< orphan*/  prism2sta_inf_scanresults (struct wlandevice*,struct hfa384x_inf_frame*) ; 
 int /*<<< orphan*/  prism2sta_inf_tallies (struct wlandevice*,struct hfa384x_inf_frame*) ; 

void prism2sta_ev_info(struct wlandevice *wlandev,
		       struct hfa384x_inf_frame *inf)
{
	le16_to_cpus(&inf->infotype);
	/* Dispatch */
	switch (inf->infotype) {
	case HFA384x_IT_HANDOVERADDR:
		prism2sta_inf_handover(wlandev, inf);
		break;
	case HFA384x_IT_COMMTALLIES:
		prism2sta_inf_tallies(wlandev, inf);
		break;
	case HFA384x_IT_HOSTSCANRESULTS:
		prism2sta_inf_hostscanresults(wlandev, inf);
		break;
	case HFA384x_IT_SCANRESULTS:
		prism2sta_inf_scanresults(wlandev, inf);
		break;
	case HFA384x_IT_CHINFORESULTS:
		prism2sta_inf_chinforesults(wlandev, inf);
		break;
	case HFA384x_IT_LINKSTATUS:
		prism2sta_inf_linkstatus(wlandev, inf);
		break;
	case HFA384x_IT_ASSOCSTATUS:
		prism2sta_inf_assocstatus(wlandev, inf);
		break;
	case HFA384x_IT_AUTHREQ:
		prism2sta_inf_authreq(wlandev, inf);
		break;
	case HFA384x_IT_PSUSERCNT:
		prism2sta_inf_psusercnt(wlandev, inf);
		break;
	case HFA384x_IT_KEYIDCHANGED:
		netdev_warn(wlandev->netdev, "Unhandled IT_KEYIDCHANGED\n");
		break;
	case HFA384x_IT_ASSOCREQ:
		netdev_warn(wlandev->netdev, "Unhandled IT_ASSOCREQ\n");
		break;
	case HFA384x_IT_MICFAILURE:
		netdev_warn(wlandev->netdev, "Unhandled IT_MICFAILURE\n");
		break;
	default:
		netdev_warn(wlandev->netdev,
			    "Unknown info type=0x%02x\n", inf->infotype);
		break;
	}
}