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
struct wmi_tlv_swba_parse {int tim_done; int noa_done; void const* ev; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
#define  WMI_TLV_TAG_ARRAY_STRUCT 129 
#define  WMI_TLV_TAG_STRUCT_HOST_SWBA_EVENT 128 
 int ath10k_wmi_tlv_iter (struct ath10k*,void const*,int,int /*<<< orphan*/ ,struct wmi_tlv_swba_parse*) ; 
 int /*<<< orphan*/  ath10k_wmi_tlv_swba_noa_parse ; 
 int /*<<< orphan*/  ath10k_wmi_tlv_swba_tim_parse ; 

__attribute__((used)) static int ath10k_wmi_tlv_swba_parse(struct ath10k *ar, u16 tag, u16 len,
				     const void *ptr, void *data)
{
	struct wmi_tlv_swba_parse *swba = data;
	int ret;

	switch (tag) {
	case WMI_TLV_TAG_STRUCT_HOST_SWBA_EVENT:
		swba->ev = ptr;
		break;
	case WMI_TLV_TAG_ARRAY_STRUCT:
		if (!swba->tim_done) {
			swba->tim_done = true;
			ret = ath10k_wmi_tlv_iter(ar, ptr, len,
						  ath10k_wmi_tlv_swba_tim_parse,
						  swba);
			if (ret)
				return ret;
		} else if (!swba->noa_done) {
			swba->noa_done = true;
			ret = ath10k_wmi_tlv_iter(ar, ptr, len,
						  ath10k_wmi_tlv_swba_noa_parse,
						  swba);
			if (ret)
				return ret;
		}
		break;
	default:
		break;
	}
	return 0;
}