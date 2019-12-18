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
struct nau8825 {int /*<<< orphan*/  dev; int /*<<< orphan*/  xtalk_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int down_timeout (int /*<<< orphan*/ *,long) ; 
 int down_trylock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nau8825_sema_acquire(struct nau8825 *nau8825, long timeout)
{
	int ret;

	if (timeout) {
		ret = down_timeout(&nau8825->xtalk_sem, timeout);
		if (ret < 0)
			dev_warn(nau8825->dev, "Acquire semaphore timeout\n");
	} else {
		ret = down_trylock(&nau8825->xtalk_sem);
		if (ret)
			dev_warn(nau8825->dev, "Acquire semaphore fail\n");
	}

	return ret;
}