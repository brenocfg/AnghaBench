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
struct tcindex_filter_result {int /*<<< orphan*/  rwork; int /*<<< orphan*/  exts; int /*<<< orphan*/  res; } ;
struct tcindex_filter {int /*<<< orphan*/  result; int /*<<< orphan*/  next; } ;
struct tcindex_data {int hash; int /*<<< orphan*/  rwork; int /*<<< orphan*/ * h; struct tcindex_filter_result* perfect; } ;
struct tcf_proto {int /*<<< orphan*/  root; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tcindex_destroy_rexts (struct tcindex_filter_result*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct tcf_proto*,struct tcindex_data*) ; 
 void* rtnl_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ tcf_exts_get_net (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_unbind_filter (struct tcf_proto*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcindex_delete (struct tcf_proto*,int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcindex_destroy_rexts_work ; 
 int /*<<< orphan*/  tcindex_destroy_work ; 

__attribute__((used)) static void tcindex_destroy(struct tcf_proto *tp, bool rtnl_held,
			    struct netlink_ext_ack *extack)
{
	struct tcindex_data *p = rtnl_dereference(tp->root);
	int i;

	pr_debug("tcindex_destroy(tp %p),p %p\n", tp, p);

	if (p->perfect) {
		for (i = 0; i < p->hash; i++) {
			struct tcindex_filter_result *r = p->perfect + i;

			tcf_unbind_filter(tp, &r->res);
			if (tcf_exts_get_net(&r->exts))
				tcf_queue_work(&r->rwork,
					       tcindex_destroy_rexts_work);
			else
				__tcindex_destroy_rexts(r);
		}
	}

	for (i = 0; p->h && i < p->hash; i++) {
		struct tcindex_filter *f, *next;
		bool last;

		for (f = rtnl_dereference(p->h[i]); f; f = next) {
			next = rtnl_dereference(f->next);
			tcindex_delete(tp, &f->result, &last, rtnl_held, NULL);
		}
	}

	tcf_queue_work(&p->rwork, tcindex_destroy_work);
}