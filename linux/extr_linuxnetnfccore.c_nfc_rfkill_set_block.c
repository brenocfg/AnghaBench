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
struct nfc_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfc_dev_down (struct nfc_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nfc_rfkill_set_block(void *data, bool blocked)
{
	struct nfc_dev *dev = data;

	pr_debug("%s blocked %d", dev_name(&dev->dev), blocked);

	if (!blocked)
		return 0;

	nfc_dev_down(dev);

	return 0;
}