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
struct tcf_proto {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* put ) (struct tcf_proto*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct tcf_proto*,void*) ; 

__attribute__((used)) static void tfilter_put(struct tcf_proto *tp, void *fh)
{
	if (tp->ops->put && fh)
		tp->ops->put(tp, fh);
}