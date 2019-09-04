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
struct subchannel_id {int /*<<< orphan*/  sch_no; } ;
struct qdio_ssqd_desc {int dummy; } ;
struct ccw_device {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ccw_device_get_schid (struct ccw_device*,struct subchannel_id*) ; 
 int qdio_setup_get_ssqd (int /*<<< orphan*/ *,struct subchannel_id*,struct qdio_ssqd_desc*) ; 

int qdio_get_ssqd_desc(struct ccw_device *cdev,
		       struct qdio_ssqd_desc *data)
{
	struct subchannel_id schid;

	if (!cdev || !cdev->private)
		return -EINVAL;

	ccw_device_get_schid(cdev, &schid);
	DBF_EVENT("get ssqd:%4x", schid.sch_no);
	return qdio_setup_get_ssqd(NULL, &schid, data);
}