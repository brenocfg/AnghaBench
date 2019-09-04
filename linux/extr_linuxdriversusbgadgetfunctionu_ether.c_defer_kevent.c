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
struct eth_dev {int /*<<< orphan*/  work; int /*<<< orphan*/  todo; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct eth_dev*,char*,int) ; 
 int /*<<< orphan*/  ERROR (struct eth_dev*,char*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void defer_kevent(struct eth_dev *dev, int flag)
{
	if (test_and_set_bit(flag, &dev->todo))
		return;
	if (!schedule_work(&dev->work))
		ERROR(dev, "kevent %d may have been dropped\n", flag);
	else
		DBG(dev, "kevent %d scheduled\n", flag);
}