#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ ** urb; int /*<<< orphan*/ * buffer; } ;
struct usX2Ydev {TYPE_1__ AS04; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int URBS_AsyncSeq ; 
 int URB_DataLen_AsyncSeq ; 
 int /*<<< orphan*/  i_usX2Y_Out04Int ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usX2Ydev*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 
 int usb_urb_ep_type_check (int /*<<< orphan*/ *) ; 

int usX2Y_AsyncSeq04_init(struct usX2Ydev *usX2Y)
{
	int	err = 0,
		i;

	usX2Y->AS04.buffer = kmalloc_array(URBS_AsyncSeq,
					   URB_DataLen_AsyncSeq, GFP_KERNEL);
	if (NULL == usX2Y->AS04.buffer) {
		err = -ENOMEM;
	} else
		for (i = 0; i < URBS_AsyncSeq; ++i) {
			if (NULL == (usX2Y->AS04.urb[i] = usb_alloc_urb(0, GFP_KERNEL))) {
				err = -ENOMEM;
				break;
			}
			usb_fill_bulk_urb(	usX2Y->AS04.urb[i], usX2Y->dev,
						usb_sndbulkpipe(usX2Y->dev, 0x04),
						usX2Y->AS04.buffer + URB_DataLen_AsyncSeq*i, 0,
						i_usX2Y_Out04Int, usX2Y
				);
			err = usb_urb_ep_type_check(usX2Y->AS04.urb[i]);
			if (err < 0)
				break;
		}
	return err;
}