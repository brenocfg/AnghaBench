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
struct TYPE_4__ {int /*<<< orphan*/  class; } ;
struct TYPE_5__ {TYPE_1__ res; } ;
struct tcindex_filter {TYPE_2__ result; int /*<<< orphan*/  next; } ;
struct tcindex_data {int hash; int /*<<< orphan*/ * h; TYPE_2__* perfect; } ;
struct tcf_walker {scalar_t__ count; scalar_t__ skip; scalar_t__ (* fn ) (struct tcf_proto*,TYPE_2__*,struct tcf_walker*) ;int stop; } ;
struct tcf_proto {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,struct tcf_proto*,struct tcf_walker*,struct tcindex_data*) ; 
 void* rtnl_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct tcf_proto*,TYPE_2__*,struct tcf_walker*) ; 
 scalar_t__ stub2 (struct tcf_proto*,TYPE_2__*,struct tcf_walker*) ; 

__attribute__((used)) static void tcindex_walk(struct tcf_proto *tp, struct tcf_walker *walker,
			 bool rtnl_held)
{
	struct tcindex_data *p = rtnl_dereference(tp->root);
	struct tcindex_filter *f, *next;
	int i;

	pr_debug("tcindex_walk(tp %p,walker %p),p %p\n", tp, walker, p);
	if (p->perfect) {
		for (i = 0; i < p->hash; i++) {
			if (!p->perfect[i].res.class)
				continue;
			if (walker->count >= walker->skip) {
				if (walker->fn(tp, p->perfect + i, walker) < 0) {
					walker->stop = 1;
					return;
				}
			}
			walker->count++;
		}
	}
	if (!p->h)
		return;
	for (i = 0; i < p->hash; i++) {
		for (f = rtnl_dereference(p->h[i]); f; f = next) {
			next = rtnl_dereference(f->next);
			if (walker->count >= walker->skip) {
				if (walker->fn(tp, &f->result, walker) < 0) {
					walker->stop = 1;
					return;
				}
			}
			walker->count++;
		}
	}
}