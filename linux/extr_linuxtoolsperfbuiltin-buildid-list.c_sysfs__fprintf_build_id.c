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
typedef  int /*<<< orphan*/  sbuild_id ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINVAL ; 
 int SBUILD_ID_SIZE ; 
 int fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int sysfs__sprintf_build_id (char*,char*) ; 

__attribute__((used)) static int sysfs__fprintf_build_id(FILE *fp)
{
	char sbuild_id[SBUILD_ID_SIZE];
	int ret;

	ret = sysfs__sprintf_build_id("/", sbuild_id);
	if (ret != sizeof(sbuild_id))
		return ret < 0 ? ret : -EINVAL;

	return fprintf(fp, "%s\n", sbuild_id);
}