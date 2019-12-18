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
struct ctl_table_header {int /*<<< orphan*/  unregistering; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unuse_table(struct ctl_table_header *p)
{
	if (!--p->used)
		if (unlikely(p->unregistering))
			complete(p->unregistering);
}