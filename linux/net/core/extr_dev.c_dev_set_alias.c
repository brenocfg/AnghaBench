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
struct net_device {int /*<<< orphan*/  ifalias; } ;
struct dev_ifalias {scalar_t__* ifalias; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t IFALIASZ ; 
 int /*<<< orphan*/  ifalias_mutex ; 
 int /*<<< orphan*/  kfree_rcu (struct dev_ifalias*,int /*<<< orphan*/ ) ; 
 struct dev_ifalias* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,size_t) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_swap_protected (int /*<<< orphan*/ ,struct dev_ifalias*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcuhead ; 

int dev_set_alias(struct net_device *dev, const char *alias, size_t len)
{
	struct dev_ifalias *new_alias = NULL;

	if (len >= IFALIASZ)
		return -EINVAL;

	if (len) {
		new_alias = kmalloc(sizeof(*new_alias) + len + 1, GFP_KERNEL);
		if (!new_alias)
			return -ENOMEM;

		memcpy(new_alias->ifalias, alias, len);
		new_alias->ifalias[len] = 0;
	}

	mutex_lock(&ifalias_mutex);
	rcu_swap_protected(dev->ifalias, new_alias,
			   mutex_is_locked(&ifalias_mutex));
	mutex_unlock(&ifalias_mutex);

	if (new_alias)
		kfree_rcu(new_alias, rcuhead);

	return len;
}