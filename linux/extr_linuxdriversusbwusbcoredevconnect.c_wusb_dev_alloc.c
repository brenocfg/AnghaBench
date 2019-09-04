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
struct wusb_dev {int /*<<< orphan*/  devconnect_acked_work; struct wusbhc* wusbhc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct wusb_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wusb_dev_free (struct wusb_dev*) ; 
 int /*<<< orphan*/  wusbhc_devconnect_acked_work ; 

__attribute__((used)) static struct wusb_dev *wusb_dev_alloc(struct wusbhc *wusbhc)
{
	struct wusb_dev *wusb_dev;

	wusb_dev = kzalloc(sizeof(*wusb_dev), GFP_KERNEL);
	if (wusb_dev == NULL)
		goto err;

	wusb_dev->wusbhc = wusbhc;

	INIT_WORK(&wusb_dev->devconnect_acked_work, wusbhc_devconnect_acked_work);

	return wusb_dev;
err:
	wusb_dev_free(wusb_dev);
	return NULL;
}