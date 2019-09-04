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
struct nau8824 {int /*<<< orphan*/  dev; int /*<<< orphan*/  jd_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int down_interruptible (int /*<<< orphan*/ *) ; 
 int down_timeout (int /*<<< orphan*/ *,long) ; 

__attribute__((used)) static int nau8824_sema_acquire(struct nau8824 *nau8824, long timeout)
{
	int ret;

	if (timeout) {
		ret = down_timeout(&nau8824->jd_sem, timeout);
		if (ret < 0)
			dev_warn(nau8824->dev, "Acquire semaphore timeout\n");
	} else {
		ret = down_interruptible(&nau8824->jd_sem);
		if (ret < 0)
			dev_warn(nau8824->dev, "Acquire semaphore fail\n");
	}

	return ret;
}