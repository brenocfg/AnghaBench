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
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsg_store_removable (int /*<<< orphan*/ ,char const*,size_t) ; 
 TYPE_1__* to_fsg_lun_opts (struct config_item*) ; 

__attribute__((used)) static ssize_t fsg_lun_opts_removable_store(struct config_item *item,
				       const char *page, size_t len)
{
	return fsg_store_removable(to_fsg_lun_opts(item)->lun, page, len);
}