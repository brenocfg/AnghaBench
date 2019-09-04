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
typedef  int u16 ;
struct wmi_svc_avail_ev_arg {void const* service_map_ext; int /*<<< orphan*/  service_map_ext_len; } ;
struct ath10k {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EPROTO ; 
#define  WMI_TLV_TAG_STRUCT_SERVICE_AVAILABLE_EVENT 128 

__attribute__((used)) static int ath10k_wmi_tlv_svc_avail_parse(struct ath10k *ar, u16 tag, u16 len,
					  const void *ptr, void *data)
{
	struct wmi_svc_avail_ev_arg *arg = data;

	switch (tag) {
	case WMI_TLV_TAG_STRUCT_SERVICE_AVAILABLE_EVENT:
		arg->service_map_ext_len = *(__le32 *)ptr;
		arg->service_map_ext = ptr + sizeof(__le32);
		return 0;
	default:
		break;
	}
	return -EPROTO;
}