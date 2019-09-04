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
typedef  int /*<<< orphan*/  notes ;
typedef  int /*<<< orphan*/  build_id ;

/* Variables and functions */
 int BUILD_ID_SIZE ; 
 int PATH_MAX ; 
 int build_id__sprintf (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char const*) ; 
 int sysfs__read_build_id (char*,int /*<<< orphan*/ *,int) ; 

int sysfs__sprintf_build_id(const char *root_dir, char *sbuild_id)
{
	char notes[PATH_MAX];
	u8 build_id[BUILD_ID_SIZE];
	int ret;

	if (!root_dir)
		root_dir = "";

	scnprintf(notes, sizeof(notes), "%s/sys/kernel/notes", root_dir);

	ret = sysfs__read_build_id(notes, build_id, sizeof(build_id));
	if (ret < 0)
		return ret;

	return build_id__sprintf(build_id, sizeof(build_id), sbuild_id);
}