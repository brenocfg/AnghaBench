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
typedef  void* u32 ;
struct wmi_scan_ev_arg {int /*<<< orphan*/  vdev_id; int /*<<< orphan*/  scan_id; int /*<<< orphan*/  scan_req_id; int /*<<< orphan*/  channel_freq; int /*<<< orphan*/  reason; int /*<<< orphan*/  event_type; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct ath10k {int /*<<< orphan*/  data_lock; TYPE_1__ scan; } ;
typedef  enum wmi_scan_event_type { ____Placeholder_wmi_scan_event_type } wmi_scan_event_type ;
typedef  enum wmi_scan_completion_reason { ____Placeholder_wmi_scan_completion_reason } wmi_scan_completion_reason ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
#define  WMI_SCAN_EVENT_BSS_CHANNEL 136 
#define  WMI_SCAN_EVENT_COMPLETED 135 
#define  WMI_SCAN_EVENT_DEQUEUED 134 
#define  WMI_SCAN_EVENT_FOREIGN_CHANNEL 133 
#define  WMI_SCAN_EVENT_FOREIGN_CHANNEL_EXIT 132 
#define  WMI_SCAN_EVENT_PREEMPTED 131 
#define  WMI_SCAN_EVENT_RESTARTED 130 
#define  WMI_SCAN_EVENT_STARTED 129 
#define  WMI_SCAN_EVENT_START_FAILED 128 
 void* __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,void*,void*,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_scan_state_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 
 int /*<<< orphan*/  ath10k_wmi_event_scan_bss_chan (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_scan_completed (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_scan_foreign_chan (struct ath10k*,void*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_scan_start_failed (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_scan_started (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_scan_type_str (int,int) ; 
 int ath10k_wmi_pull_scan (struct ath10k*,struct sk_buff*,struct wmi_scan_ev_arg*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int ath10k_wmi_event_scan(struct ath10k *ar, struct sk_buff *skb)
{
	struct wmi_scan_ev_arg arg = {};
	enum wmi_scan_event_type event_type;
	enum wmi_scan_completion_reason reason;
	u32 freq;
	u32 req_id;
	u32 scan_id;
	u32 vdev_id;
	int ret;

	ret = ath10k_wmi_pull_scan(ar, skb, &arg);
	if (ret) {
		ath10k_warn(ar, "failed to parse scan event: %d\n", ret);
		return ret;
	}

	event_type = __le32_to_cpu(arg.event_type);
	reason = __le32_to_cpu(arg.reason);
	freq = __le32_to_cpu(arg.channel_freq);
	req_id = __le32_to_cpu(arg.scan_req_id);
	scan_id = __le32_to_cpu(arg.scan_id);
	vdev_id = __le32_to_cpu(arg.vdev_id);

	spin_lock_bh(&ar->data_lock);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "scan event %s type %d reason %d freq %d req_id %d scan_id %d vdev_id %d state %s (%d)\n",
		   ath10k_wmi_event_scan_type_str(event_type, reason),
		   event_type, reason, freq, req_id, scan_id, vdev_id,
		   ath10k_scan_state_str(ar->scan.state), ar->scan.state);

	switch (event_type) {
	case WMI_SCAN_EVENT_STARTED:
		ath10k_wmi_event_scan_started(ar);
		break;
	case WMI_SCAN_EVENT_COMPLETED:
		ath10k_wmi_event_scan_completed(ar);
		break;
	case WMI_SCAN_EVENT_BSS_CHANNEL:
		ath10k_wmi_event_scan_bss_chan(ar);
		break;
	case WMI_SCAN_EVENT_FOREIGN_CHANNEL:
		ath10k_wmi_event_scan_foreign_chan(ar, freq);
		break;
	case WMI_SCAN_EVENT_START_FAILED:
		ath10k_warn(ar, "received scan start failure event\n");
		ath10k_wmi_event_scan_start_failed(ar);
		break;
	case WMI_SCAN_EVENT_DEQUEUED:
	case WMI_SCAN_EVENT_PREEMPTED:
	case WMI_SCAN_EVENT_RESTARTED:
	case WMI_SCAN_EVENT_FOREIGN_CHANNEL_EXIT:
	default:
		break;
	}

	spin_unlock_bh(&ar->data_lock);
	return 0;
}