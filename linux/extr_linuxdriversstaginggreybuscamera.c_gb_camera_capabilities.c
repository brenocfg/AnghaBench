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
typedef  int /*<<< orphan*/  u8 ;
struct gb_camera {int /*<<< orphan*/  bundle; int /*<<< orphan*/  mutex; int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GB_CAMERA_TYPE_CAPABILITIES ; 
 int /*<<< orphan*/  GB_OPERATION_FLAG_SHORT_RESPONSE ; 
 int gb_camera_operation_sync_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,size_t*) ; 
 int gb_pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcam_err (struct gb_camera*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_camera_capabilities(struct gb_camera *gcam,
				  u8 *capabilities, size_t *size)
{
	int ret;

	ret = gb_pm_runtime_get_sync(gcam->bundle);
	if (ret)
		return ret;

	mutex_lock(&gcam->mutex);

	if (!gcam->connection) {
		ret = -EINVAL;
		goto done;
	}

	ret = gb_camera_operation_sync_flags(gcam->connection,
					     GB_CAMERA_TYPE_CAPABILITIES,
					     GB_OPERATION_FLAG_SHORT_RESPONSE,
					     NULL, 0,
					     (void *)capabilities, size);
	if (ret)
		gcam_err(gcam, "failed to retrieve capabilities: %d\n", ret);

done:
	mutex_unlock(&gcam->mutex);

	gb_pm_runtime_put_autosuspend(gcam->bundle);

	return ret;
}