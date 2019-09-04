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
struct wusbhc {int dummy; } ;
struct wusb_dev {int port_idx; int /*<<< orphan*/  addr; int /*<<< orphan*/  availability; } ;
struct whc {int /*<<< orphan*/  mutex; struct di_buf_entry* di_buf; } ;
struct di_buf_entry {int addr_sec_info; int /*<<< orphan*/  availability_info; } ;

/* Variables and functions */
 int WHC_DI_DEV_ADDR (int /*<<< orphan*/ ) ; 
 int WHC_DI_DEV_ADDR_MASK ; 
 int WHC_DI_DISABLE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_mas_bm_copy_le (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int whc_update_di (struct whc*,int) ; 
 struct whc* wusbhc_to_whc (struct wusbhc*) ; 

int whc_dev_info_set(struct wusbhc *wusbhc, struct wusb_dev *wusb_dev)
{
	struct whc *whc = wusbhc_to_whc(wusbhc);
	int idx = wusb_dev->port_idx;
	struct di_buf_entry *di = &whc->di_buf[idx];
	int ret;

	mutex_lock(&whc->mutex);

	uwb_mas_bm_copy_le(di->availability_info, &wusb_dev->availability);
	di->addr_sec_info &= ~(WHC_DI_DISABLE | WHC_DI_DEV_ADDR_MASK);
	di->addr_sec_info |= WHC_DI_DEV_ADDR(wusb_dev->addr);

	ret = whc_update_di(whc, idx);

	mutex_unlock(&whc->mutex);

	return ret;
}