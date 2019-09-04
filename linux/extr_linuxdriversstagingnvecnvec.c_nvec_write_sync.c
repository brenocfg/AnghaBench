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
struct nvec_msg {int dummy; } ;
struct nvec_chip {unsigned char sync_write_pending; int /*<<< orphan*/  sync_write_mutex; struct nvec_msg* last_sync_msg; int /*<<< orphan*/  dev; int /*<<< orphan*/  sync_write; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nvec_write_async (struct nvec_chip*,unsigned char const*,short) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int nvec_write_sync(struct nvec_chip *nvec,
		    const unsigned char *data, short size,
		    struct nvec_msg **msg)
{
	mutex_lock(&nvec->sync_write_mutex);

	*msg = NULL;
	nvec->sync_write_pending = (data[1] << 8) + data[0];

	if (nvec_write_async(nvec, data, size) < 0) {
		mutex_unlock(&nvec->sync_write_mutex);
		return -ENOMEM;
	}

	dev_dbg(nvec->dev, "nvec_sync_write: 0x%04x\n",
		nvec->sync_write_pending);
	if (!(wait_for_completion_timeout(&nvec->sync_write,
					  msecs_to_jiffies(2000)))) {
		dev_warn(nvec->dev,
			 "timeout waiting for sync write to complete\n");
		mutex_unlock(&nvec->sync_write_mutex);
		return -ETIMEDOUT;
	}

	dev_dbg(nvec->dev, "nvec_sync_write: pong!\n");

	*msg = nvec->last_sync_msg;

	mutex_unlock(&nvec->sync_write_mutex);

	return 0;
}