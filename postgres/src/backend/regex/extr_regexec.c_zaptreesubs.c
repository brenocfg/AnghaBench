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
struct vars {size_t nmatch; TYPE_1__* pmatch; } ;
struct subre {char op; int subno; struct subre* right; struct subre* left; } ;
struct TYPE_2__ {int rm_so; int rm_eo; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
zaptreesubs(struct vars *v,
			struct subre *t)
{
	if (t->op == '(')
	{
		int			n = t->subno;

		assert(n > 0);
		if ((size_t) n < v->nmatch)
		{
			v->pmatch[n].rm_so = -1;
			v->pmatch[n].rm_eo = -1;
		}
	}

	if (t->left != NULL)
		zaptreesubs(v, t->left);
	if (t->right != NULL)
		zaptreesubs(v, t->right);
}