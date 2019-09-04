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
struct pnp_resource {struct resource res; } ;
struct pnp_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct resource*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,struct resource*) ; 
 struct pnp_resource* pnp_new_resource (struct pnp_dev*) ; 

struct pnp_resource *pnp_add_resource(struct pnp_dev *dev,
				      struct resource *res)
{
	struct pnp_resource *pnp_res;

	pnp_res = pnp_new_resource(dev);
	if (!pnp_res) {
		dev_err(&dev->dev, "can't add resource %pR\n", res);
		return NULL;
	}

	pnp_res->res = *res;
	pnp_res->res.name = dev->name;
	dev_dbg(&dev->dev, "%pR\n", res);
	return pnp_res;
}