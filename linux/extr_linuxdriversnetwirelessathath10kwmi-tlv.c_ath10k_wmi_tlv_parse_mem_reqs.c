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
typedef  scalar_t__ u16 ;
struct wmi_svc_rdy_ev_arg {void const** mem_reqs; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (void const**) ; 
 int ENOMEM ; 
 int EPROTO ; 
 scalar_t__ WMI_TLV_TAG_STRUCT_WLAN_HOST_MEM_REQ ; 

__attribute__((used)) static int
ath10k_wmi_tlv_parse_mem_reqs(struct ath10k *ar, u16 tag, u16 len,
			      const void *ptr, void *data)
{
	struct wmi_svc_rdy_ev_arg *arg = data;
	int i;

	if (tag != WMI_TLV_TAG_STRUCT_WLAN_HOST_MEM_REQ)
		return -EPROTO;

	for (i = 0; i < ARRAY_SIZE(arg->mem_reqs); i++) {
		if (!arg->mem_reqs[i]) {
			arg->mem_reqs[i] = ptr;
			return 0;
		}
	}

	return -ENOMEM;
}