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
struct tcf_walker {int stop; scalar_t__ count; scalar_t__ skip; scalar_t__ (* fn ) (struct tcf_proto*,struct route4_filter*,struct tcf_walker*) ;} ;
struct tcf_proto {int /*<<< orphan*/  root; } ;
struct route4_head {int /*<<< orphan*/ * table; } ;
struct route4_filter {int /*<<< orphan*/  next; } ;
struct route4_bucket {int /*<<< orphan*/ * ht; } ;

/* Variables and functions */
 void* rtnl_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct tcf_proto*,struct route4_filter*,struct tcf_walker*) ; 

__attribute__((used)) static void route4_walk(struct tcf_proto *tp, struct tcf_walker *arg,
			bool rtnl_held)
{
	struct route4_head *head = rtnl_dereference(tp->root);
	unsigned int h, h1;

	if (head == NULL || arg->stop)
		return;

	for (h = 0; h <= 256; h++) {
		struct route4_bucket *b = rtnl_dereference(head->table[h]);

		if (b) {
			for (h1 = 0; h1 <= 32; h1++) {
				struct route4_filter *f;

				for (f = rtnl_dereference(b->ht[h1]);
				     f;
				     f = rtnl_dereference(f->next)) {
					if (arg->count < arg->skip) {
						arg->count++;
						continue;
					}
					if (arg->fn(tp, f, arg) < 0) {
						arg->stop = 1;
						return;
					}
					arg->count++;
				}
			}
		}
	}
}