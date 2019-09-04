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
struct regulator {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct regulator* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct regulator*) ; 
 struct regulator* _regulator_get (struct device*,char const*,int) ; 
 int /*<<< orphan*/  devm_regulator_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct regulator**) ; 
 struct regulator** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct regulator**) ; 

__attribute__((used)) static struct regulator *_devm_regulator_get(struct device *dev, const char *id,
					     int get_type)
{
	struct regulator **ptr, *regulator;

	ptr = devres_alloc(devm_regulator_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	regulator = _regulator_get(dev, id, get_type);
	if (!IS_ERR(regulator)) {
		*ptr = regulator;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return regulator;
}