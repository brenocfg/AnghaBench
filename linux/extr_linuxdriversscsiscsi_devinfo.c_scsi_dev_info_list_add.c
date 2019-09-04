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
typedef  int /*<<< orphan*/  blist_flags_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_DEVINFO_GLOBAL ; 
 int scsi_dev_info_list_add_keyed (int,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scsi_dev_info_list_add(int compatible, char *vendor, char *model,
			    char *strflags, blist_flags_t flags)
{
	return scsi_dev_info_list_add_keyed(compatible, vendor, model,
					    strflags, flags,
					    SCSI_DEVINFO_GLOBAL);
}