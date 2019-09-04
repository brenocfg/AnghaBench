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
struct nvmet_subsys {int /*<<< orphan*/  ver; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ NVME_MAJOR (int /*<<< orphan*/ ) ; 
 scalar_t__ NVME_MINOR (int /*<<< orphan*/ ) ; 
 scalar_t__ NVME_TERTIARY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,int,...) ; 
 struct nvmet_subsys* to_subsys (struct config_item*) ; 

__attribute__((used)) static ssize_t nvmet_subsys_attr_version_show(struct config_item *item,
					      char *page)
{
	struct nvmet_subsys *subsys = to_subsys(item);

	if (NVME_TERTIARY(subsys->ver))
		return snprintf(page, PAGE_SIZE, "%d.%d.%d\n",
				(int)NVME_MAJOR(subsys->ver),
				(int)NVME_MINOR(subsys->ver),
				(int)NVME_TERTIARY(subsys->ver));
	else
		return snprintf(page, PAGE_SIZE, "%d.%d\n",
				(int)NVME_MAJOR(subsys->ver),
				(int)NVME_MINOR(subsys->ver));
}