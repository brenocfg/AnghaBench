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
struct wmi_wmm_params_arg {int dummy; } ;
struct wmi_wmm_params {int dummy; } ;
struct wmi_tlv {scalar_t__ value; void* len; void* tag; } ;

/* Variables and functions */
 int WMI_TLV_TAG_STRUCT_WMM_PARAMS ; 
 void* __cpu_to_le16 (int) ; 
 int /*<<< orphan*/  ath10k_wmi_set_wmm_param (struct wmi_wmm_params*,struct wmi_wmm_params_arg const*) ; 

__attribute__((used)) static void *ath10k_wmi_tlv_put_wmm(void *ptr,
				    const struct wmi_wmm_params_arg *arg)
{
	struct wmi_wmm_params *wmm;
	struct wmi_tlv *tlv;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_WMM_PARAMS);
	tlv->len = __cpu_to_le16(sizeof(*wmm));
	wmm = (void *)tlv->value;
	ath10k_wmi_set_wmm_param(wmm, arg);

	return ptr + sizeof(*tlv) + sizeof(*wmm);
}