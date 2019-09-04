#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  void* u32 ;
typedef  int u16 ;
struct TYPE_6__ {TYPE_2__* ext_info; } ;
struct ath10k_sdio {void** mbox_size; void** mbox_addr; TYPE_3__ mbox_info; scalar_t__ swap_mbox; } ;
struct ath10k_htc {TYPE_1__* endpoint; } ;
struct ath10k {struct ath10k_htc htc; } ;
typedef  enum ath10k_htc_ep_id { ____Placeholder_ath10k_htc_ep_id } ath10k_htc_ep_id ;
struct TYPE_5__ {void* htc_ext_sz; void* htc_ext_addr; } ;
struct TYPE_4__ {int service_id; int eid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_SDIO ; 
 int ATH10K_HTC_EP_COUNT ; 
#define  ATH10K_HTC_SVC_ID_HTT_DATA_MSG 130 
#define  ATH10K_HTC_SVC_ID_RSVD_CTRL 129 
#define  ATH10K_HTC_SVC_ID_WMI_CONTROL 128 
 int EINVAL ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,void*,void*) ; 
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 

__attribute__((used)) static int ath10k_sdio_hif_map_service_to_pipe(struct ath10k *ar,
					       u16 service_id,
					       u8 *ul_pipe, u8 *dl_pipe)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	struct ath10k_htc *htc = &ar->htc;
	u32 htt_addr, wmi_addr, htt_mbox_size, wmi_mbox_size;
	enum ath10k_htc_ep_id eid;
	bool ep_found = false;
	int i;

	/* For sdio, we are interested in the mapping between eid
	 * and pipeid rather than service_id to pipe_id.
	 * First we find out which eid has been allocated to the
	 * service...
	 */
	for (i = 0; i < ATH10K_HTC_EP_COUNT; i++) {
		if (htc->endpoint[i].service_id == service_id) {
			eid = htc->endpoint[i].eid;
			ep_found = true;
			break;
		}
	}

	if (!ep_found)
		return -EINVAL;

	/* Then we create the simplest mapping possible between pipeid
	 * and eid
	 */
	*ul_pipe = *dl_pipe = (u8)eid;

	/* Normally, HTT will use the upper part of the extended
	 * mailbox address space (ext_info[1].htc_ext_addr) and WMI ctrl
	 * the lower part (ext_info[0].htc_ext_addr).
	 * If fw wants swapping of mailbox addresses, the opposite is true.
	 */
	if (ar_sdio->swap_mbox) {
		htt_addr = ar_sdio->mbox_info.ext_info[0].htc_ext_addr;
		wmi_addr = ar_sdio->mbox_info.ext_info[1].htc_ext_addr;
		htt_mbox_size = ar_sdio->mbox_info.ext_info[0].htc_ext_sz;
		wmi_mbox_size = ar_sdio->mbox_info.ext_info[1].htc_ext_sz;
	} else {
		htt_addr = ar_sdio->mbox_info.ext_info[1].htc_ext_addr;
		wmi_addr = ar_sdio->mbox_info.ext_info[0].htc_ext_addr;
		htt_mbox_size = ar_sdio->mbox_info.ext_info[1].htc_ext_sz;
		wmi_mbox_size = ar_sdio->mbox_info.ext_info[0].htc_ext_sz;
	}

	switch (service_id) {
	case ATH10K_HTC_SVC_ID_RSVD_CTRL:
		/* HTC ctrl ep mbox address has already been setup in
		 * ath10k_sdio_hif_start
		 */
		break;
	case ATH10K_HTC_SVC_ID_WMI_CONTROL:
		ar_sdio->mbox_addr[eid] = wmi_addr;
		ar_sdio->mbox_size[eid] = wmi_mbox_size;
		ath10k_dbg(ar, ATH10K_DBG_SDIO,
			   "sdio wmi ctrl mbox_addr 0x%x mbox_size %d\n",
			   ar_sdio->mbox_addr[eid], ar_sdio->mbox_size[eid]);
		break;
	case ATH10K_HTC_SVC_ID_HTT_DATA_MSG:
		ar_sdio->mbox_addr[eid] = htt_addr;
		ar_sdio->mbox_size[eid] = htt_mbox_size;
		ath10k_dbg(ar, ATH10K_DBG_SDIO,
			   "sdio htt data mbox_addr 0x%x mbox_size %d\n",
			   ar_sdio->mbox_addr[eid], ar_sdio->mbox_size[eid]);
		break;
	default:
		ath10k_warn(ar, "unsupported HTC service id: %d\n",
			    service_id);
		return -EINVAL;
	}

	return 0;
}