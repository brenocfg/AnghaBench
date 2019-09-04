#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_76__   TYPE_9__ ;
typedef  struct TYPE_75__   TYPE_8__ ;
typedef  struct TYPE_74__   TYPE_7__ ;
typedef  struct TYPE_73__   TYPE_6__ ;
typedef  struct TYPE_72__   TYPE_5__ ;
typedef  struct TYPE_71__   TYPE_4__ ;
typedef  struct TYPE_70__   TYPE_3__ ;
typedef  struct TYPE_69__   TYPE_38__ ;
typedef  struct TYPE_68__   TYPE_37__ ;
typedef  struct TYPE_67__   TYPE_36__ ;
typedef  struct TYPE_66__   TYPE_35__ ;
typedef  struct TYPE_65__   TYPE_34__ ;
typedef  struct TYPE_64__   TYPE_33__ ;
typedef  struct TYPE_63__   TYPE_32__ ;
typedef  struct TYPE_62__   TYPE_31__ ;
typedef  struct TYPE_61__   TYPE_30__ ;
typedef  struct TYPE_60__   TYPE_2__ ;
typedef  struct TYPE_59__   TYPE_29__ ;
typedef  struct TYPE_58__   TYPE_28__ ;
typedef  struct TYPE_57__   TYPE_27__ ;
typedef  struct TYPE_56__   TYPE_26__ ;
typedef  struct TYPE_55__   TYPE_25__ ;
typedef  struct TYPE_54__   TYPE_24__ ;
typedef  struct TYPE_53__   TYPE_23__ ;
typedef  struct TYPE_52__   TYPE_22__ ;
typedef  struct TYPE_51__   TYPE_21__ ;
typedef  struct TYPE_50__   TYPE_20__ ;
typedef  struct TYPE_49__   TYPE_1__ ;
typedef  struct TYPE_48__   TYPE_19__ ;
typedef  struct TYPE_47__   TYPE_18__ ;
typedef  struct TYPE_46__   TYPE_17__ ;
typedef  struct TYPE_45__   TYPE_16__ ;
typedef  struct TYPE_44__   TYPE_15__ ;
typedef  struct TYPE_43__   TYPE_14__ ;
typedef  struct TYPE_42__   TYPE_13__ ;
typedef  struct TYPE_41__   TYPE_12__ ;
typedef  struct TYPE_40__   TYPE_11__ ;
typedef  struct TYPE_39__   TYPE_10__ ;

/* Type definitions */
struct wlandevice {int /*<<< orphan*/  netdev; struct hfa384x* priv; } ;
struct TYPE_69__ {void* data; void* status; } ;
struct TYPE_68__ {int /*<<< orphan*/  data; void* status; } ;
struct TYPE_67__ {int /*<<< orphan*/  data; void* status; } ;
struct TYPE_66__ {int /*<<< orphan*/  data; void* status; } ;
struct TYPE_65__ {int /*<<< orphan*/  data; void* status; } ;
struct TYPE_64__ {int data; void* status; } ;
struct TYPE_63__ {void* data; void* status; } ;
struct TYPE_62__ {void* data; void* status; } ;
struct TYPE_61__ {void* data; void* status; } ;
struct TYPE_59__ {void* data; void* status; } ;
struct TYPE_58__ {void* data; void* status; } ;
struct TYPE_57__ {scalar_t__ data; void* status; } ;
struct TYPE_56__ {scalar_t__ data; void* status; } ;
struct TYPE_55__ {scalar_t__ data; void* status; } ;
struct TYPE_54__ {scalar_t__ data; void* status; } ;
struct TYPE_53__ {scalar_t__ data; void* status; } ;
struct TYPE_52__ {scalar_t__ data; void* status; } ;
struct TYPE_51__ {scalar_t__ data; void* status; } ;
struct TYPE_50__ {scalar_t__ data; void* status; } ;
struct TYPE_48__ {scalar_t__ data; void* status; } ;
struct TYPE_47__ {scalar_t__ data; void* status; } ;
struct TYPE_46__ {scalar_t__ data; void* status; } ;
struct TYPE_45__ {scalar_t__ data; void* status; } ;
struct TYPE_44__ {scalar_t__ data; void* status; } ;
struct TYPE_43__ {scalar_t__ data; void* status; } ;
struct TYPE_42__ {scalar_t__ data; void* status; } ;
struct TYPE_41__ {scalar_t__ data; void* status; } ;
struct TYPE_39__ {void* len; int /*<<< orphan*/  data; } ;
struct TYPE_40__ {TYPE_10__ data; void* status; } ;
struct TYPE_74__ {int /*<<< orphan*/  data; void* len; } ;
struct TYPE_75__ {TYPE_7__ data; void* status; } ;
struct TYPE_73__ {void* data; void* status; } ;
struct TYPE_72__ {void* data; void* status; } ;
struct TYPE_71__ {int data; } ;
struct p80211msg_dot11req_scan_results {TYPE_38__ resultcode; TYPE_37__ bsstype; TYPE_36__ cfpollreq; TYPE_35__ cfpollable; TYPE_34__ privacy; TYPE_33__ capinfo; TYPE_32__ dschannel; TYPE_31__ ibssatimwindow; TYPE_30__ localtime; TYPE_29__ timestamp; TYPE_28__ beaconperiod; TYPE_27__ supprate8; TYPE_26__ supprate7; TYPE_25__ supprate6; TYPE_24__ supprate5; TYPE_23__ supprate4; TYPE_22__ supprate3; TYPE_21__ supprate2; TYPE_20__ supprate1; TYPE_19__ basicrate8; TYPE_18__ basicrate7; TYPE_17__ basicrate6; TYPE_16__ basicrate5; TYPE_15__ basicrate4; TYPE_14__ basicrate3; TYPE_13__ basicrate2; TYPE_12__ basicrate1; TYPE_11__ ssid; TYPE_8__ bssid; TYPE_6__ noise; TYPE_5__ signal; TYPE_4__ bssindex; } ;
struct TYPE_76__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct hfa384x_hscan_result_sub {scalar_t__* supprates; int /*<<< orphan*/  capinfo; int /*<<< orphan*/  chid; int /*<<< orphan*/  atim; int /*<<< orphan*/  bcnint; TYPE_9__ ssid; int /*<<< orphan*/  bssid; int /*<<< orphan*/  anl; int /*<<< orphan*/  sl; } ;
struct hfa384x {TYPE_3__* scanresults; } ;
struct TYPE_49__ {struct hfa384x_hscan_result_sub* result; } ;
struct TYPE_60__ {TYPE_1__ hscanresult; } ;
struct TYPE_70__ {int framelen; TYPE_2__ info; } ;

/* Variables and functions */
 scalar_t__ DOT11_RATE5_ISBASIC_GET (scalar_t__) ; 
 int HFA384x_SCANRESULT_MAX ; 
 int /*<<< orphan*/  P80211ENUM_bsstype_independent ; 
 int /*<<< orphan*/  P80211ENUM_bsstype_infrastructure ; 
 void* P80211ENUM_msgitem_status_data_ok ; 
 void* P80211ENUM_resultcode_invalid_parameters ; 
 void* P80211ENUM_resultcode_success ; 
 void* WLAN_BSSID_LEN ; 
 int /*<<< orphan*/  WLAN_GET_MGMT_CAP_INFO_CFPOLLABLE (int) ; 
 int /*<<< orphan*/  WLAN_GET_MGMT_CAP_INFO_CFPOLLREQ (int) ; 
 scalar_t__ WLAN_GET_MGMT_CAP_INFO_ESS (int) ; 
 int /*<<< orphan*/  WLAN_GET_MGMT_CAP_INFO_PRIVACY (int) ; 
 int /*<<< orphan*/  WLAN_SSID_MAXLEN ; 
 void* jiffies ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 void* min_t (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  u16 ; 

int prism2mgmt_scan_results(struct wlandevice *wlandev, void *msgp)
{
	int result = 0;
	struct p80211msg_dot11req_scan_results *req;
	struct hfa384x *hw = wlandev->priv;
	struct hfa384x_hscan_result_sub *item = NULL;

	int count;

	req = msgp;

	req->resultcode.status = P80211ENUM_msgitem_status_data_ok;

	if (!hw->scanresults) {
		netdev_err(wlandev->netdev,
			   "dot11req_scan_results can only be used after a successful dot11req_scan.\n");
		result = 2;
		req->resultcode.data = P80211ENUM_resultcode_invalid_parameters;
		goto exit;
	}

	count = (hw->scanresults->framelen - 3) / 32;
	if (count > HFA384x_SCANRESULT_MAX)
		count = HFA384x_SCANRESULT_MAX;

	if (req->bssindex.data >= count) {
		netdev_dbg(wlandev->netdev,
			   "requested index (%d) out of range (%d)\n",
			   req->bssindex.data, count);
		result = 2;
		req->resultcode.data = P80211ENUM_resultcode_invalid_parameters;
		goto exit;
	}

	item = &hw->scanresults->info.hscanresult.result[req->bssindex.data];
	/* signal and noise */
	req->signal.status = P80211ENUM_msgitem_status_data_ok;
	req->noise.status = P80211ENUM_msgitem_status_data_ok;
	req->signal.data = le16_to_cpu(item->sl);
	req->noise.data = le16_to_cpu(item->anl);

	/* BSSID */
	req->bssid.status = P80211ENUM_msgitem_status_data_ok;
	req->bssid.data.len = WLAN_BSSID_LEN;
	memcpy(req->bssid.data.data, item->bssid, WLAN_BSSID_LEN);

	/* SSID */
	req->ssid.status = P80211ENUM_msgitem_status_data_ok;
	req->ssid.data.len = le16_to_cpu(item->ssid.len);
	req->ssid.data.len = min_t(u16, req->ssid.data.len, WLAN_SSID_MAXLEN);
	memcpy(req->ssid.data.data, item->ssid.data, req->ssid.data.len);

	/* supported rates */
	for (count = 0; count < 10; count++)
		if (item->supprates[count] == 0)
			break;

#define REQBASICRATE(N) \
	do { \
		if ((count >= (N)) && DOT11_RATE5_ISBASIC_GET(	\
			item->supprates[(N) - 1])) { \
			req->basicrate ## N .data = item->supprates[(N) - 1]; \
			req->basicrate ## N .status = \
				P80211ENUM_msgitem_status_data_ok; \
		} \
	} while (0)

	REQBASICRATE(1);
	REQBASICRATE(2);
	REQBASICRATE(3);
	REQBASICRATE(4);
	REQBASICRATE(5);
	REQBASICRATE(6);
	REQBASICRATE(7);
	REQBASICRATE(8);

#define REQSUPPRATE(N) \
	do { \
		if (count >= (N)) {					\
			req->supprate ## N .data = item->supprates[(N) - 1]; \
			req->supprate ## N .status = \
				P80211ENUM_msgitem_status_data_ok; \
		} \
	} while (0)

	REQSUPPRATE(1);
	REQSUPPRATE(2);
	REQSUPPRATE(3);
	REQSUPPRATE(4);
	REQSUPPRATE(5);
	REQSUPPRATE(6);
	REQSUPPRATE(7);
	REQSUPPRATE(8);

	/* beacon period */
	req->beaconperiod.status = P80211ENUM_msgitem_status_data_ok;
	req->beaconperiod.data = le16_to_cpu(item->bcnint);

	/* timestamps */
	req->timestamp.status = P80211ENUM_msgitem_status_data_ok;
	req->timestamp.data = jiffies;
	req->localtime.status = P80211ENUM_msgitem_status_data_ok;
	req->localtime.data = jiffies;

	/* atim window */
	req->ibssatimwindow.status = P80211ENUM_msgitem_status_data_ok;
	req->ibssatimwindow.data = le16_to_cpu(item->atim);

	/* Channel */
	req->dschannel.status = P80211ENUM_msgitem_status_data_ok;
	req->dschannel.data = le16_to_cpu(item->chid);

	/* capinfo bits */
	count = le16_to_cpu(item->capinfo);
	req->capinfo.status = P80211ENUM_msgitem_status_data_ok;
	req->capinfo.data = count;

	/* privacy flag */
	req->privacy.status = P80211ENUM_msgitem_status_data_ok;
	req->privacy.data = WLAN_GET_MGMT_CAP_INFO_PRIVACY(count);

	/* cfpollable */
	req->cfpollable.status = P80211ENUM_msgitem_status_data_ok;
	req->cfpollable.data = WLAN_GET_MGMT_CAP_INFO_CFPOLLABLE(count);

	/* cfpollreq */
	req->cfpollreq.status = P80211ENUM_msgitem_status_data_ok;
	req->cfpollreq.data = WLAN_GET_MGMT_CAP_INFO_CFPOLLREQ(count);

	/* bsstype */
	req->bsstype.status = P80211ENUM_msgitem_status_data_ok;
	req->bsstype.data = (WLAN_GET_MGMT_CAP_INFO_ESS(count)) ?
	    P80211ENUM_bsstype_infrastructure : P80211ENUM_bsstype_independent;

	result = 0;
	req->resultcode.data = P80211ENUM_resultcode_success;

exit:
	return result;
}