#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ruleId; scalar_t__ event; scalar_t__ enabled; scalar_t__ isInstead; int /*<<< orphan*/  actions; int /*<<< orphan*/  qual; } ;
struct TYPE_5__ {int numLocks; TYPE_2__** rules; } ;
typedef  TYPE_1__ RuleLock ;
typedef  TYPE_2__ RewriteRule ;

/* Variables and functions */
 int /*<<< orphan*/  equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
equalRuleLocks(RuleLock *rlock1, RuleLock *rlock2)
{
	int			i;

	/*
	 * As of 7.3 we assume the rule ordering is repeatable, because
	 * RelationBuildRuleLock should read 'em in a consistent order.  So just
	 * compare corresponding slots.
	 */
	if (rlock1 != NULL)
	{
		if (rlock2 == NULL)
			return false;
		if (rlock1->numLocks != rlock2->numLocks)
			return false;
		for (i = 0; i < rlock1->numLocks; i++)
		{
			RewriteRule *rule1 = rlock1->rules[i];
			RewriteRule *rule2 = rlock2->rules[i];

			if (rule1->ruleId != rule2->ruleId)
				return false;
			if (rule1->event != rule2->event)
				return false;
			if (rule1->enabled != rule2->enabled)
				return false;
			if (rule1->isInstead != rule2->isInstead)
				return false;
			if (!equal(rule1->qual, rule2->qual))
				return false;
			if (!equal(rule1->actions, rule2->actions))
				return false;
		}
	}
	else if (rlock2 != NULL)
		return false;
	return true;
}