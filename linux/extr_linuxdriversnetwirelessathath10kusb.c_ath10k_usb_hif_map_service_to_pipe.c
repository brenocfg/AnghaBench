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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct ath10k {int dummy; } ;

/* Variables and functions */
#define  ATH10K_HTC_SVC_ID_HTT_DATA_MSG 130 
#define  ATH10K_HTC_SVC_ID_RSVD_CTRL 129 
#define  ATH10K_HTC_SVC_ID_WMI_CONTROL 128 
 int /*<<< orphan*/  ATH10K_USB_PIPE_RX_DATA ; 
 int /*<<< orphan*/  ATH10K_USB_PIPE_TX_CTRL ; 
 int /*<<< orphan*/  ATH10K_USB_PIPE_TX_DATA_LP ; 
 int EPERM ; 

__attribute__((used)) static int ath10k_usb_hif_map_service_to_pipe(struct ath10k *ar, u16 svc_id,
					      u8 *ul_pipe, u8 *dl_pipe)
{
	switch (svc_id) {
	case ATH10K_HTC_SVC_ID_RSVD_CTRL:
	case ATH10K_HTC_SVC_ID_WMI_CONTROL:
		*ul_pipe = ATH10K_USB_PIPE_TX_CTRL;
		/* due to large control packets, shift to data pipe */
		*dl_pipe = ATH10K_USB_PIPE_RX_DATA;
		break;
	case ATH10K_HTC_SVC_ID_HTT_DATA_MSG:
		*ul_pipe = ATH10K_USB_PIPE_TX_DATA_LP;
		/* Disable rxdata2 directly, it will be enabled
		 * if FW enable rxdata2
		 */
		*dl_pipe = ATH10K_USB_PIPE_RX_DATA;
		break;
	default:
		return -EPERM;
	}

	return 0;
}