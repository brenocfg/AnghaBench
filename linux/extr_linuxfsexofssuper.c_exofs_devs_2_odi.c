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
struct osd_dev_info {int osdname_len; void* systemid_len; scalar_t__* osdname; int /*<<< orphan*/  systemid; } ;
struct exofs_dt_device_info {scalar_t__* osdname; scalar_t__ long_name_offset; int /*<<< orphan*/  osdname_len; int /*<<< orphan*/  systemid; int /*<<< orphan*/  systemid_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OSD_SYSTEMID_LEN ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int exofs_devs_2_odi(struct exofs_dt_device_info *dt_dev,
			     struct osd_dev_info *odi)
{
	odi->systemid_len = le32_to_cpu(dt_dev->systemid_len);
	if (likely(odi->systemid_len))
		memcpy(odi->systemid, dt_dev->systemid, OSD_SYSTEMID_LEN);

	odi->osdname_len = le32_to_cpu(dt_dev->osdname_len);
	odi->osdname = dt_dev->osdname;

	/* FIXME support long names. Will need a _put function */
	if (dt_dev->long_name_offset)
		return -EINVAL;

	/* Make sure osdname is printable!
	 * mkexofs should give us space for a null-terminator else the
	 * device-table is invalid.
	 */
	if (unlikely(odi->osdname_len >= sizeof(dt_dev->osdname)))
		odi->osdname_len = sizeof(dt_dev->osdname) - 1;
	dt_dev->osdname[odi->osdname_len] = 0;

	/* If it's all zeros something is bad we read past end-of-obj */
	return !(odi->systemid_len || odi->osdname_len);
}