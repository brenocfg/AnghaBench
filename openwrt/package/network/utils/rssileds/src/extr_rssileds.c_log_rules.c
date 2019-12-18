#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  bfactor; int /*<<< orphan*/  boffset; int /*<<< orphan*/  maxq; int /*<<< orphan*/  minq; TYPE_1__* led; } ;
typedef  TYPE_2__ rule_t ;
struct TYPE_4__ {int /*<<< orphan*/  sysfspath; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void log_rules(rule_t *rules)
{
	rule_t *rule = rules;
	while (rule)
	{
		syslog(LOG_INFO, " %s r: %d..%d, o: %d, f: %d\n",
			rule->led->sysfspath,
			rule->minq, rule->maxq,
			rule->boffset, rule->bfactor);
		rule = rule->next;
	}
}