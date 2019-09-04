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
struct f_hid_opts {int report_desc_length; int /*<<< orphan*/  lock; int /*<<< orphan*/  report_desc; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct f_hid_opts* to_f_hid_opts (struct config_item*) ; 

__attribute__((used)) static ssize_t f_hid_opts_report_desc_show(struct config_item *item, char *page)
{
	struct f_hid_opts *opts = to_f_hid_opts(item);
	int result;

	mutex_lock(&opts->lock);
	result = opts->report_desc_length;
	memcpy(page, opts->report_desc, opts->report_desc_length);
	mutex_unlock(&opts->lock);

	return result;
}