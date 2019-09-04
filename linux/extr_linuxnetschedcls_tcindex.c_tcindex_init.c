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
struct tcindex_data {int mask; int fall_through; int /*<<< orphan*/  hash; } ;
struct tcf_proto {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_HASH_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct tcindex_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct tcf_proto*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct tcindex_data*) ; 

__attribute__((used)) static int tcindex_init(struct tcf_proto *tp)
{
	struct tcindex_data *p;

	pr_debug("tcindex_init(tp %p)\n", tp);
	p = kzalloc(sizeof(struct tcindex_data), GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	p->mask = 0xffff;
	p->hash = DEFAULT_HASH_SIZE;
	p->fall_through = 1;

	rcu_assign_pointer(tp->root, p);
	return 0;
}