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
struct tcf_walker {int stop; scalar_t__ count; scalar_t__ skip; scalar_t__ (* fn ) (struct tcf_proto*,struct rsvp_filter*,struct tcf_walker*) ;} ;
struct tcf_proto {int /*<<< orphan*/  root; } ;
struct rsvp_session {int /*<<< orphan*/ * ht; int /*<<< orphan*/  next; } ;
struct rsvp_head {int /*<<< orphan*/ * ht; } ;
struct rsvp_filter {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 void* rtnl_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct tcf_proto*,struct rsvp_filter*,struct tcf_walker*) ; 

__attribute__((used)) static void rsvp_walk(struct tcf_proto *tp, struct tcf_walker *arg,
		      bool rtnl_held)
{
	struct rsvp_head *head = rtnl_dereference(tp->root);
	unsigned int h, h1;

	if (arg->stop)
		return;

	for (h = 0; h < 256; h++) {
		struct rsvp_session *s;

		for (s = rtnl_dereference(head->ht[h]); s;
		     s = rtnl_dereference(s->next)) {
			for (h1 = 0; h1 <= 16; h1++) {
				struct rsvp_filter *f;

				for (f = rtnl_dereference(s->ht[h1]); f;
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