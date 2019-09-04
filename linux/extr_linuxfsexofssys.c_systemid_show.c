#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct osd_dev_info {int /*<<< orphan*/  systemid_len; int /*<<< orphan*/  systemid; } ;
struct osd_dev {int dummy; } ;
struct TYPE_2__ {struct osd_dev* od; } ;
struct exofs_dev {TYPE_1__ ored; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct osd_dev_info* osduld_device_info (struct osd_dev*) ; 

__attribute__((used)) static ssize_t systemid_show(struct exofs_dev *edp, char *buf)
{
	struct osd_dev *odev = edp->ored.od;
	const struct osd_dev_info *odi = osduld_device_info(odev);

	memcpy(buf, odi->systemid, odi->systemid_len);
	return odi->systemid_len;
}