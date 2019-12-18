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
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINVAL ; 
 int __perf_pmu__new_alias (struct list_head*,char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strim (char*) ; 

__attribute__((used)) static int perf_pmu__new_alias(struct list_head *list, char *dir, char *name, FILE *file)
{
	char buf[256];
	int ret;

	ret = fread(buf, 1, sizeof(buf), file);
	if (ret == 0)
		return -EINVAL;

	buf[ret] = 0;

	/* Remove trailing newline from sysfs file */
	strim(buf);

	return __perf_pmu__new_alias(list, dir, name, NULL, buf, NULL, NULL, NULL,
				     NULL, NULL, NULL);
}