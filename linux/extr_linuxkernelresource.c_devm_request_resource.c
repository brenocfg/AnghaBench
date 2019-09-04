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
struct resource {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,struct resource*,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  devm_resource_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct resource**) ; 
 struct resource** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct resource**) ; 
 struct resource* request_resource_conflict (struct resource*,struct resource*) ; 

int devm_request_resource(struct device *dev, struct resource *root,
			  struct resource *new)
{
	struct resource *conflict, **ptr;

	ptr = devres_alloc(devm_resource_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return -ENOMEM;

	*ptr = new;

	conflict = request_resource_conflict(root, new);
	if (conflict) {
		dev_err(dev, "resource collision: %pR conflicts with %s %pR\n",
			new, conflict->name, conflict);
		devres_free(ptr);
		return -EBUSY;
	}

	devres_add(dev, ptr);
	return 0;
}