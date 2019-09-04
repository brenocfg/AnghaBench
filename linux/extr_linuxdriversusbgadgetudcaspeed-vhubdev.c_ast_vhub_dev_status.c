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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int is_selfpowered; } ;
struct ast_vhub_dev {int /*<<< orphan*/  ep0; scalar_t__ wakeup_en; TYPE_1__ gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDBG (struct ast_vhub_dev*,char*) ; 
 int USB_DEVICE_REMOTE_WAKEUP ; 
 int USB_DEVICE_SELF_POWERED ; 
 int ast_vhub_simple_reply (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ast_vhub_dev_status(struct ast_vhub_dev *d,
			       u16 wIndex, u16 wValue)
{
	u8 st0;

	DDBG(d, "GET_STATUS(dev)\n");

	st0 = d->gadget.is_selfpowered << USB_DEVICE_SELF_POWERED;
	if (d->wakeup_en)
		st0 |= 1 << USB_DEVICE_REMOTE_WAKEUP;

	return ast_vhub_simple_reply(&d->ep0, st0, 0);
}