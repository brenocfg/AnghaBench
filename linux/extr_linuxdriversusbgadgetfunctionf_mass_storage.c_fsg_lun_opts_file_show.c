#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fsg_opts {TYPE_3__* common; } ;
struct TYPE_4__ {int /*<<< orphan*/  ci_parent; } ;
struct TYPE_5__ {TYPE_1__ cg_item; } ;
struct fsg_lun_opts {int /*<<< orphan*/  lun; TYPE_2__ group; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_6__ {int /*<<< orphan*/  filesem; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsg_show_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct fsg_lun_opts* to_fsg_lun_opts (struct config_item*) ; 
 struct fsg_opts* to_fsg_opts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t fsg_lun_opts_file_show(struct config_item *item, char *page)
{
	struct fsg_lun_opts *opts = to_fsg_lun_opts(item);
	struct fsg_opts *fsg_opts = to_fsg_opts(opts->group.cg_item.ci_parent);

	return fsg_show_file(opts->lun, &fsg_opts->common->filesem, page);
}