#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/ * dst; } ;
struct inet_cork_full {int /*<<< orphan*/  fl; TYPE_1__ base; } ;
struct inet6_cork {TYPE_2__* opt; } ;
struct TYPE_4__ {struct TYPE_4__* srcrt; struct TYPE_4__* hopopt; struct TYPE_4__* dst1opt; struct TYPE_4__* dst0opt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPCORK_ALLFRAG ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ip6_cork_release(struct inet_cork_full *cork,
			     struct inet6_cork *v6_cork)
{
	if (v6_cork->opt) {
		kfree(v6_cork->opt->dst0opt);
		kfree(v6_cork->opt->dst1opt);
		kfree(v6_cork->opt->hopopt);
		kfree(v6_cork->opt->srcrt);
		kfree(v6_cork->opt);
		v6_cork->opt = NULL;
	}

	if (cork->base.dst) {
		dst_release(cork->base.dst);
		cork->base.dst = NULL;
		cork->base.flags &= ~IPCORK_ALLFRAG;
	}
	memset(&cork->fl, 0, sizeof(cork->fl));
}