#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int name_len; char* name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ drm_version_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_IOCTL_VERSION ; 
 int ioctl (int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int strcmp (char*,char*) ; 

int check_vgem(int fd)
{
	drm_version_t version = { 0 };
	char name[5];
	int ret;

	version.name_len = 4;
	version.name = name;

	ret = ioctl(fd, DRM_IOCTL_VERSION, &version);
	if (ret)
		return 1;

	return strcmp(name, "vgem");
}