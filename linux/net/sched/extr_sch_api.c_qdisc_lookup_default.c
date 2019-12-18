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
struct Qdisc_ops {int /*<<< orphan*/  owner; int /*<<< orphan*/  id; struct Qdisc_ops* next; } ;

/* Variables and functions */
 struct Qdisc_ops* qdisc_base ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct Qdisc_ops *qdisc_lookup_default(const char *name)
{
	struct Qdisc_ops *q = NULL;

	for (q = qdisc_base; q; q = q->next) {
		if (!strcmp(name, q->id)) {
			if (!try_module_get(q->owner))
				q = NULL;
			break;
		}
	}

	return q;
}