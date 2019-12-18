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
 int filename__sprintf_build_id (char const*,char*) ; 
 int fprintf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int filename__fprintf_build_id(const char *name, FILE *fp)
{
	char sbuild_id[SBUILD_ID_SIZE];
	int ret;

	ret = filename__sprintf_build_id(name, sbuild_id);
	if (ret != sizeof(sbuild_id))
		return ret < 0 ? ret : -EINVAL;

	return fprintf(fp, "%s\n", sbuild_id);
}