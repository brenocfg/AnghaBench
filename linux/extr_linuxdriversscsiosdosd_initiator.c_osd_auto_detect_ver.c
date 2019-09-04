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
struct osd_dev_info {int dummy; } ;
struct osd_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSD_DEBUG (char*) ; 
 int /*<<< orphan*/  OSD_VER1 ; 
 int _osd_get_print_system_info (struct osd_dev*,void*,struct osd_dev_info*) ; 
 int /*<<< orphan*/  osd_dev_set_ver (struct osd_dev*,int /*<<< orphan*/ ) ; 

int osd_auto_detect_ver(struct osd_dev *od,
	void *caps, struct osd_dev_info *odi)
{
	int ret;

	/* Auto-detect the osd version */
	ret = _osd_get_print_system_info(od, caps, odi);
	if (ret) {
		osd_dev_set_ver(od, OSD_VER1);
		OSD_DEBUG("converting to OSD1\n");
		ret = _osd_get_print_system_info(od, caps, odi);
	}

	return ret;
}