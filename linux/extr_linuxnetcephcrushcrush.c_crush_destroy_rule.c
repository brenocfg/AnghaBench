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
struct crush_rule {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct crush_rule*) ; 

void crush_destroy_rule(struct crush_rule *rule)
{
	kfree(rule);
}