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
struct fib_rule {scalar_t__ action; scalar_t__ table; scalar_t__ l3mdev; } ;

/* Variables and functions */
 scalar_t__ FR_ACT_TO_TBL ; 
 scalar_t__ RT_TABLE_DEFAULT ; 
 scalar_t__ RT_TABLE_LOCAL ; 
 scalar_t__ RT_TABLE_MAIN ; 
 int /*<<< orphan*/  fib4_rule_matchall (struct fib_rule const*) ; 

bool fib4_rule_default(const struct fib_rule *rule)
{
	if (!fib4_rule_matchall(rule) || rule->action != FR_ACT_TO_TBL ||
	    rule->l3mdev)
		return false;
	if (rule->table != RT_TABLE_LOCAL && rule->table != RT_TABLE_MAIN &&
	    rule->table != RT_TABLE_DEFAULT)
		return false;
	return true;
}