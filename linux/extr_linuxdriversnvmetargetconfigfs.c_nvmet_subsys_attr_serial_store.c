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
struct nvmet_subsys {int /*<<< orphan*/  serial; } ;
struct config_item {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_config_sem ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int /*<<< orphan*/ *) ; 
 struct nvmet_subsys* to_subsys (struct config_item*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t nvmet_subsys_attr_serial_store(struct config_item *item,
					      const char *page, size_t count)
{
	struct nvmet_subsys *subsys = to_subsys(item);

	down_write(&nvmet_config_sem);
	sscanf(page, "%llx\n", &subsys->serial);
	up_write(&nvmet_config_sem);

	return count;
}