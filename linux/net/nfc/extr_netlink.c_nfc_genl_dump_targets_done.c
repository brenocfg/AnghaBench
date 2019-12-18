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
struct nfc_dev {int dummy; } ;
struct netlink_callback {scalar_t__* args; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfc_put_device (struct nfc_dev*) ; 

__attribute__((used)) static int nfc_genl_dump_targets_done(struct netlink_callback *cb)
{
	struct nfc_dev *dev = (struct nfc_dev *) cb->args[1];

	if (dev)
		nfc_put_device(dev);

	return 0;
}