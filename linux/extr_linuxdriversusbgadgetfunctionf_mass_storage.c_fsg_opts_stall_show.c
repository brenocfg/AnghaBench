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
struct fsg_opts {int /*<<< orphan*/  lock; TYPE_1__* common; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int can_stall; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int) ; 
 struct fsg_opts* to_fsg_opts (struct config_item*) ; 

__attribute__((used)) static ssize_t fsg_opts_stall_show(struct config_item *item, char *page)
{
	struct fsg_opts *opts = to_fsg_opts(item);
	int result;

	mutex_lock(&opts->lock);
	result = sprintf(page, "%d", opts->common->can_stall);
	mutex_unlock(&opts->lock);

	return result;
}