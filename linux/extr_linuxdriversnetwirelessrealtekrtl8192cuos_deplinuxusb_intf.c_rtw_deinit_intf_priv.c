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
struct dvobj_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _SUCCESS ; 

__attribute__((used)) static u8 rtw_deinit_intf_priv(struct dvobj_priv *dvobj)
{
	u8 rst = _SUCCESS;

	#ifdef CONFIG_USB_VENDOR_REQ_BUFFER_PREALLOC
	if(dvobj->usb_vendor_req_buf)
		rtw_mfree(dvobj->usb_alloc_vendor_req_buf, MAX_USB_IO_CTL_SIZE);
	#endif

	#ifdef CONFIG_USB_VENDOR_REQ_MUTEX
	_rtw_mutex_free(&dvobj->usb_vendor_req_mutex);
	#endif

	return rst;
}