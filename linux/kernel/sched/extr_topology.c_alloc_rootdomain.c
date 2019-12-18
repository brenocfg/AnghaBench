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
struct root_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ init_rootdomain (struct root_domain*) ; 
 int /*<<< orphan*/  kfree (struct root_domain*) ; 
 struct root_domain* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct root_domain *alloc_rootdomain(void)
{
	struct root_domain *rd;

	rd = kzalloc(sizeof(*rd), GFP_KERNEL);
	if (!rd)
		return NULL;

	if (init_rootdomain(rd) != 0) {
		kfree(rd);
		return NULL;
	}

	return rd;
}