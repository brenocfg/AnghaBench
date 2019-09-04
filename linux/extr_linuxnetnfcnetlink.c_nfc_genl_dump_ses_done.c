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
struct netlink_callback {scalar_t__* args; } ;
struct class_dev_iter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct class_dev_iter*) ; 
 int /*<<< orphan*/  nfc_device_iter_exit (struct class_dev_iter*) ; 

__attribute__((used)) static int nfc_genl_dump_ses_done(struct netlink_callback *cb)
{
	struct class_dev_iter *iter = (struct class_dev_iter *) cb->args[0];

	nfc_device_iter_exit(iter);
	kfree(iter);

	return 0;
}