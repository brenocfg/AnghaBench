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
struct gadget_info {int use_os_desc; int /*<<< orphan*/  lock; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct gadget_info* os_desc_item_to_gadget_info (struct config_item*) ; 
 int strtobool (char const*,int*) ; 

__attribute__((used)) static ssize_t os_desc_use_store(struct config_item *item, const char *page,
				 size_t len)
{
	struct gadget_info *gi = os_desc_item_to_gadget_info(item);
	int ret;
	bool use;

	mutex_lock(&gi->lock);
	ret = strtobool(page, &use);
	if (!ret) {
		gi->use_os_desc = use;
		ret = len;
	}
	mutex_unlock(&gi->lock);

	return ret;
}