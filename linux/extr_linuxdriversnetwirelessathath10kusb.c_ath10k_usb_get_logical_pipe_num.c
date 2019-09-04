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
typedef  int u8 ;

/* Variables and functions */
#define  ATH10K_USB_EP_ADDR_APP_CTRL_IN 135 
#define  ATH10K_USB_EP_ADDR_APP_CTRL_OUT 134 
#define  ATH10K_USB_EP_ADDR_APP_DATA2_IN 133 
#define  ATH10K_USB_EP_ADDR_APP_DATA_HP_OUT 132 
#define  ATH10K_USB_EP_ADDR_APP_DATA_IN 131 
#define  ATH10K_USB_EP_ADDR_APP_DATA_LP_OUT 130 
#define  ATH10K_USB_EP_ADDR_APP_DATA_MP_OUT 129 
#define  ATH10K_USB_EP_ADDR_APP_INT_IN 128 
 int ATH10K_USB_PIPE_INVALID ; 
 int ATH10K_USB_PIPE_RX_CTRL ; 
 int ATH10K_USB_PIPE_RX_DATA ; 
 int ATH10K_USB_PIPE_RX_DATA2 ; 
 int ATH10K_USB_PIPE_RX_INT ; 
 int ATH10K_USB_PIPE_TX_CTRL ; 
 int ATH10K_USB_PIPE_TX_DATA_HP ; 
 int ATH10K_USB_PIPE_TX_DATA_LP ; 
 int ATH10K_USB_PIPE_TX_DATA_MP ; 
 int RX_URB_COUNT ; 
 int TX_URB_COUNT ; 

__attribute__((used)) static u8 ath10k_usb_get_logical_pipe_num(u8 ep_address, int *urb_count)
{
	u8 pipe_num = ATH10K_USB_PIPE_INVALID;

	switch (ep_address) {
	case ATH10K_USB_EP_ADDR_APP_CTRL_IN:
		pipe_num = ATH10K_USB_PIPE_RX_CTRL;
		*urb_count = RX_URB_COUNT;
		break;
	case ATH10K_USB_EP_ADDR_APP_DATA_IN:
		pipe_num = ATH10K_USB_PIPE_RX_DATA;
		*urb_count = RX_URB_COUNT;
		break;
	case ATH10K_USB_EP_ADDR_APP_INT_IN:
		pipe_num = ATH10K_USB_PIPE_RX_INT;
		*urb_count = RX_URB_COUNT;
		break;
	case ATH10K_USB_EP_ADDR_APP_DATA2_IN:
		pipe_num = ATH10K_USB_PIPE_RX_DATA2;
		*urb_count = RX_URB_COUNT;
		break;
	case ATH10K_USB_EP_ADDR_APP_CTRL_OUT:
		pipe_num = ATH10K_USB_PIPE_TX_CTRL;
		*urb_count = TX_URB_COUNT;
		break;
	case ATH10K_USB_EP_ADDR_APP_DATA_LP_OUT:
		pipe_num = ATH10K_USB_PIPE_TX_DATA_LP;
		*urb_count = TX_URB_COUNT;
		break;
	case ATH10K_USB_EP_ADDR_APP_DATA_MP_OUT:
		pipe_num = ATH10K_USB_PIPE_TX_DATA_MP;
		*urb_count = TX_URB_COUNT;
		break;
	case ATH10K_USB_EP_ADDR_APP_DATA_HP_OUT:
		pipe_num = ATH10K_USB_PIPE_TX_DATA_HP;
		*urb_count = TX_URB_COUNT;
		break;
	default:
		/* note: there may be endpoints not currently used */
		break;
	}

	return pipe_num;
}