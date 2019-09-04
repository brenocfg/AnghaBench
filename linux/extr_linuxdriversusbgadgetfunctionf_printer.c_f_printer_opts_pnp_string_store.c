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
struct f_printer_opts {int pnp_string_allocated; char* pnp_string; int /*<<< orphan*/  lock; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrndup (char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct f_printer_opts* to_f_printer_opts (struct config_item*) ; 

__attribute__((used)) static ssize_t f_printer_opts_pnp_string_store(struct config_item *item,
					       const char *page, size_t len)
{
	struct f_printer_opts *opts = to_f_printer_opts(item);
	char *new_pnp;
	int result;

	mutex_lock(&opts->lock);

	new_pnp = kstrndup(page, len, GFP_KERNEL);
	if (!new_pnp) {
		result = -ENOMEM;
		goto unlock;
	}

	if (opts->pnp_string_allocated)
		kfree(opts->pnp_string);

	opts->pnp_string_allocated = true;
	opts->pnp_string = new_pnp;
	result = len;
unlock:
	mutex_unlock(&opts->lock);

	return result;
}