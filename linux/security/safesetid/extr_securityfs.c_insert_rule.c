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
struct setuid_ruleset {int /*<<< orphan*/  rules; } ;
struct setuid_rule {int /*<<< orphan*/  src_uid; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  __kuid_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void insert_rule(struct setuid_ruleset *pol, struct setuid_rule *rule)
{
	hash_add(pol->rules, &rule->next, __kuid_val(rule->src_uid));
}