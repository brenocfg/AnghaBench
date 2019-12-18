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
struct genl_ops {scalar_t__ cmd; int /*<<< orphan*/ * doit; int /*<<< orphan*/ * dumpit; } ;
struct genl_family {unsigned int n_ops; struct genl_ops* ops; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static int genl_validate_ops(const struct genl_family *family)
{
	const struct genl_ops *ops = family->ops;
	unsigned int n_ops = family->n_ops;
	int i, j;

	if (WARN_ON(n_ops && !ops))
		return -EINVAL;

	if (!n_ops)
		return 0;

	for (i = 0; i < n_ops; i++) {
		if (ops[i].dumpit == NULL && ops[i].doit == NULL)
			return -EINVAL;
		for (j = i + 1; j < n_ops; j++)
			if (ops[i].cmd == ops[j].cmd)
				return -EINVAL;
	}

	return 0;
}