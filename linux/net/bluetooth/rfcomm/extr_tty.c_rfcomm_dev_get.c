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
struct rfcomm_dev {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 struct rfcomm_dev* __rfcomm_dev_lookup (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_dev_lock ; 
 int /*<<< orphan*/  tty_port_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rfcomm_dev *rfcomm_dev_get(int id)
{
	struct rfcomm_dev *dev;

	mutex_lock(&rfcomm_dev_lock);

	dev = __rfcomm_dev_lookup(id);

	if (dev && !tty_port_get(&dev->port))
		dev = NULL;

	mutex_unlock(&rfcomm_dev_lock);

	return dev;
}