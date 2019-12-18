#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tcindex_filter_result {int dummy; } ;
struct tcindex_data {int hash; TYPE_1__* perfect; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  exts; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TCA_TCINDEX_ACT ; 
 int /*<<< orphan*/  TCA_TCINDEX_POLICE ; 
 TYPE_1__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int tcf_exts_init (int /*<<< orphan*/ *,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcindex_free_perfect_hash (struct tcindex_data*) ; 

__attribute__((used)) static int tcindex_alloc_perfect_hash(struct net *net, struct tcindex_data *cp)
{
	int i, err = 0;

	cp->perfect = kcalloc(cp->hash, sizeof(struct tcindex_filter_result),
			      GFP_KERNEL);
	if (!cp->perfect)
		return -ENOMEM;

	for (i = 0; i < cp->hash; i++) {
		err = tcf_exts_init(&cp->perfect[i].exts, net,
				    TCA_TCINDEX_ACT, TCA_TCINDEX_POLICE);
		if (err < 0)
			goto errout;
	}

	return 0;

errout:
	tcindex_free_perfect_hash(cp);
	return err;
}