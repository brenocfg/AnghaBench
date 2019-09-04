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
struct nvme_ctrl {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVME_LOG_CHANGED_NS ; 
 int NVME_MAX_CHANGED_NAMESPACES ; 
 int /*<<< orphan*/  NVME_NSID_ALL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int nvme_get_log (struct nvme_ctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvme_clear_changed_ns_log(struct nvme_ctrl *ctrl)
{
	size_t log_size = NVME_MAX_CHANGED_NAMESPACES * sizeof(__le32);
	__le32 *log;
	int error;

	log = kzalloc(log_size, GFP_KERNEL);
	if (!log)
		return;

	/*
	 * We need to read the log to clear the AEN, but we don't want to rely
	 * on it for the changed namespace information as userspace could have
	 * raced with us in reading the log page, which could cause us to miss
	 * updates.
	 */
	error = nvme_get_log(ctrl, NVME_NSID_ALL, NVME_LOG_CHANGED_NS, 0, log,
			log_size, 0);
	if (error)
		dev_warn(ctrl->device,
			"reading changed ns log failed: %d\n", error);

	kfree(log);
}