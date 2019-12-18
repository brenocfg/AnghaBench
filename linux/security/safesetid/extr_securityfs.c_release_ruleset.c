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
struct setuid_ruleset {int /*<<< orphan*/  rcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  __release_ruleset ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_ruleset(struct setuid_ruleset *pol)
{
	call_rcu(&pol->rcu, __release_ruleset);
}