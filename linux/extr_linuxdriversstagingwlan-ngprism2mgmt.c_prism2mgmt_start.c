#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_9__ ;
typedef  struct TYPE_43__   TYPE_8__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_22__ ;
typedef  struct TYPE_35__   TYPE_21__ ;
typedef  struct TYPE_34__   TYPE_20__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_19__ ;
typedef  struct TYPE_31__   TYPE_18__ ;
typedef  struct TYPE_30__   TYPE_17__ ;
typedef  struct TYPE_29__   TYPE_16__ ;
typedef  struct TYPE_28__   TYPE_15__ ;
typedef  struct TYPE_27__   TYPE_14__ ;
typedef  struct TYPE_26__   TYPE_13__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct wlandevice {int /*<<< orphan*/  netdev; int /*<<< orphan*/  macmode; int /*<<< orphan*/  ssid; struct hfa384x* priv; } ;
struct p80211pstrd {int dummy; } ;
struct TYPE_37__ {int /*<<< orphan*/  data; scalar_t__ status; } ;
struct TYPE_36__ {scalar_t__ data; } ;
struct TYPE_35__ {scalar_t__ status; int /*<<< orphan*/  data; } ;
struct TYPE_34__ {scalar_t__ status; int /*<<< orphan*/  data; } ;
struct TYPE_32__ {scalar_t__ status; int /*<<< orphan*/  data; } ;
struct TYPE_31__ {scalar_t__ status; int /*<<< orphan*/  data; } ;
struct TYPE_30__ {scalar_t__ status; int /*<<< orphan*/  data; } ;
struct TYPE_29__ {scalar_t__ status; int /*<<< orphan*/  data; } ;
struct TYPE_28__ {scalar_t__ status; int /*<<< orphan*/  data; } ;
struct TYPE_27__ {int /*<<< orphan*/  data; } ;
struct TYPE_26__ {scalar_t__ status; int /*<<< orphan*/  data; } ;
struct TYPE_25__ {scalar_t__ status; int /*<<< orphan*/  data; } ;
struct TYPE_24__ {scalar_t__ status; int /*<<< orphan*/  data; } ;
struct TYPE_23__ {scalar_t__ status; int /*<<< orphan*/  data; } ;
struct TYPE_44__ {scalar_t__ status; int /*<<< orphan*/  data; } ;
struct TYPE_43__ {scalar_t__ status; int /*<<< orphan*/  data; } ;
struct TYPE_42__ {scalar_t__ status; int /*<<< orphan*/  data; } ;
struct TYPE_41__ {int /*<<< orphan*/  data; } ;
struct TYPE_40__ {int data; } ;
struct TYPE_39__ {int data; } ;
struct TYPE_38__ {int /*<<< orphan*/  data; } ;
struct p80211msg_dot11req_start {TYPE_2__ resultcode; TYPE_22__ bsstype; TYPE_21__ operationalrate8; TYPE_20__ operationalrate7; TYPE_19__ operationalrate6; TYPE_18__ operationalrate5; TYPE_17__ operationalrate4; TYPE_16__ operationalrate3; TYPE_15__ operationalrate2; TYPE_14__ operationalrate1; TYPE_13__ basicrate8; TYPE_12__ basicrate7; TYPE_11__ basicrate6; TYPE_10__ basicrate5; TYPE_9__ basicrate4; TYPE_8__ basicrate3; TYPE_7__ basicrate2; TYPE_6__ basicrate1; TYPE_5__ dschannel; TYPE_4__ beaconperiod; TYPE_3__ ssid; } ;
struct hfa384x_bytestr {int dummy; } ;
struct TYPE_33__ {int minor; int variant; int /*<<< orphan*/  major; } ;
struct hfa384x {TYPE_1__ ident_sta_fw; } ;

/* Variables and functions */
 scalar_t__ HFA384x_FIRMWARE_VERSION (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  HFA384x_RID_CNFAPBCNINT ; 
 int /*<<< orphan*/  HFA384x_RID_CNFBASICRATES ; 
 int /*<<< orphan*/  HFA384x_RID_CNFDESIREDSSID ; 
 int /*<<< orphan*/  HFA384x_RID_CNFDESIREDSSID_LEN ; 
 int /*<<< orphan*/  HFA384x_RID_CNFMAXDATALEN ; 
 int /*<<< orphan*/  HFA384x_RID_CNFOWNCHANNEL ; 
 int /*<<< orphan*/  HFA384x_RID_CNFOWNSSID ; 
 int /*<<< orphan*/  HFA384x_RID_CNFOWNSSID_LEN ; 
 int /*<<< orphan*/  HFA384x_RID_CNFPORTTYPE ; 
 int /*<<< orphan*/  HFA384x_RID_CNFSUPPRATES ; 
 int /*<<< orphan*/  HFA384x_RID_TXRATECNTL ; 
 scalar_t__ P80211ENUM_bsstype_independent ; 
 scalar_t__ P80211ENUM_msgitem_status_data_ok ; 
 int /*<<< orphan*/  P80211ENUM_resultcode_invalid_parameters ; 
 int /*<<< orphan*/  P80211ENUM_resultcode_not_supported ; 
 int /*<<< orphan*/  P80211ENUM_resultcode_success ; 
 int /*<<< orphan*/  WLAN_MACMODE_IBSS_STA ; 
 int /*<<< orphan*/  WLAN_MACMODE_NONE ; 
 int hfa384x_drvr_enable (struct hfa384x*,int /*<<< orphan*/ ) ; 
 int hfa384x_drvr_setconfig (struct hfa384x*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hfa384x_drvr_setconfig16 (struct hfa384x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 
 int p80211rate_to_p2bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prism2mgmt_pstr2bytestr (struct hfa384x_bytestr*,struct p80211pstrd*) ; 

int prism2mgmt_start(struct wlandevice *wlandev, void *msgp)
{
	int result = 0;
	struct hfa384x *hw = wlandev->priv;
	struct p80211msg_dot11req_start *msg = msgp;

	struct p80211pstrd *pstr;
	u8 bytebuf[80];
	struct hfa384x_bytestr *p2bytestr = (struct hfa384x_bytestr *)bytebuf;
	u16 word;

	wlandev->macmode = WLAN_MACMODE_NONE;

	/* Set the SSID */
	memcpy(&wlandev->ssid, &msg->ssid.data, sizeof(msg->ssid.data));

	/*** ADHOC IBSS ***/
	/* see if current f/w is less than 8c3 */
	if (HFA384x_FIRMWARE_VERSION(hw->ident_sta_fw.major,
				     hw->ident_sta_fw.minor,
				     hw->ident_sta_fw.variant) <
	    HFA384x_FIRMWARE_VERSION(0, 8, 3)) {
		/* Ad-Hoc not quite supported on Prism2 */
		msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
		msg->resultcode.data = P80211ENUM_resultcode_not_supported;
		goto done;
	}

	msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;

	/*** STATION ***/
	/* Set the REQUIRED config items */
	/* SSID */
	pstr = (struct p80211pstrd *)&msg->ssid.data;
	prism2mgmt_pstr2bytestr(p2bytestr, pstr);
	result = hfa384x_drvr_setconfig(hw, HFA384x_RID_CNFOWNSSID,
					bytebuf, HFA384x_RID_CNFOWNSSID_LEN);
	if (result) {
		netdev_err(wlandev->netdev, "Failed to set CnfOwnSSID\n");
		goto failed;
	}
	result = hfa384x_drvr_setconfig(hw, HFA384x_RID_CNFDESIREDSSID,
					bytebuf,
					HFA384x_RID_CNFDESIREDSSID_LEN);
	if (result) {
		netdev_err(wlandev->netdev, "Failed to set CnfDesiredSSID\n");
		goto failed;
	}

	/* bsstype - we use the default in the ap firmware */
	/* IBSS port */
	hfa384x_drvr_setconfig16(hw, HFA384x_RID_CNFPORTTYPE, 0);

	/* beacon period */
	word = msg->beaconperiod.data;
	result = hfa384x_drvr_setconfig16(hw, HFA384x_RID_CNFAPBCNINT, word);
	if (result) {
		netdev_err(wlandev->netdev,
			   "Failed to set beacon period=%d.\n", word);
		goto failed;
	}

	/* dschannel */
	word = msg->dschannel.data;
	result = hfa384x_drvr_setconfig16(hw, HFA384x_RID_CNFOWNCHANNEL, word);
	if (result) {
		netdev_err(wlandev->netdev,
			   "Failed to set channel=%d.\n", word);
		goto failed;
	}
	/* Basic rates */
	word = p80211rate_to_p2bit(msg->basicrate1.data);
	if (msg->basicrate2.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->basicrate2.data);

	if (msg->basicrate3.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->basicrate3.data);

	if (msg->basicrate4.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->basicrate4.data);

	if (msg->basicrate5.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->basicrate5.data);

	if (msg->basicrate6.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->basicrate6.data);

	if (msg->basicrate7.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->basicrate7.data);

	if (msg->basicrate8.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->basicrate8.data);

	result = hfa384x_drvr_setconfig16(hw, HFA384x_RID_CNFBASICRATES, word);
	if (result) {
		netdev_err(wlandev->netdev,
			   "Failed to set basicrates=%d.\n", word);
		goto failed;
	}

	/* Operational rates (supprates and txratecontrol) */
	word = p80211rate_to_p2bit(msg->operationalrate1.data);
	if (msg->operationalrate2.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->operationalrate2.data);

	if (msg->operationalrate3.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->operationalrate3.data);

	if (msg->operationalrate4.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->operationalrate4.data);

	if (msg->operationalrate5.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->operationalrate5.data);

	if (msg->operationalrate6.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->operationalrate6.data);

	if (msg->operationalrate7.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->operationalrate7.data);

	if (msg->operationalrate8.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->operationalrate8.data);

	result = hfa384x_drvr_setconfig16(hw, HFA384x_RID_CNFSUPPRATES, word);
	if (result) {
		netdev_err(wlandev->netdev,
			   "Failed to set supprates=%d.\n", word);
		goto failed;
	}

	result = hfa384x_drvr_setconfig16(hw, HFA384x_RID_TXRATECNTL, word);
	if (result) {
		netdev_err(wlandev->netdev, "Failed to set txrates=%d.\n",
			   word);
		goto failed;
	}

	/* Set the macmode so the frame setup code knows what to do */
	if (msg->bsstype.data == P80211ENUM_bsstype_independent) {
		wlandev->macmode = WLAN_MACMODE_IBSS_STA;
		/* lets extend the data length a bit */
		hfa384x_drvr_setconfig16(hw, HFA384x_RID_CNFMAXDATALEN, 2304);
	}

	/* Enable the Port */
	result = hfa384x_drvr_enable(hw, 0);
	if (result) {
		netdev_err(wlandev->netdev,
			   "Enable macport failed, result=%d.\n", result);
		goto failed;
	}

	msg->resultcode.data = P80211ENUM_resultcode_success;

	goto done;
failed:
	netdev_dbg(wlandev->netdev,
		   "Failed to set a config option, result=%d\n", result);
	msg->resultcode.data = P80211ENUM_resultcode_invalid_parameters;

done:
	return 0;
}