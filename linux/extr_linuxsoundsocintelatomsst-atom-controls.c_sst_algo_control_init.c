#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sst_algo_control {int /*<<< orphan*/ * params; int /*<<< orphan*/  max; } ;
struct device {int dummy; } ;
struct TYPE_3__ {scalar_t__ private_value; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * devm_kzalloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* sst_algo_controls ; 

__attribute__((used)) static int sst_algo_control_init(struct device *dev)
{
	int i = 0;
	struct sst_algo_control *bc;
	/*allocate space to cache the algo parameters in the driver*/
	for (i = 0; i < ARRAY_SIZE(sst_algo_controls); i++) {
		bc = (struct sst_algo_control *)sst_algo_controls[i].private_value;
		bc->params = devm_kzalloc(dev, bc->max, GFP_KERNEL);
		if (bc->params == NULL)
			return -ENOMEM;
	}
	return 0;
}