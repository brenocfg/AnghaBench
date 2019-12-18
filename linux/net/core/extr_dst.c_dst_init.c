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
struct net_device {int dummy; } ;
struct dst_ops {int dummy; } ;
struct dst_entry {unsigned long expires; int obsolete; unsigned short flags; int /*<<< orphan*/  lastuse; scalar_t__ __use; int /*<<< orphan*/  __refcnt; int /*<<< orphan*/ * lwtstate; scalar_t__ tclassid; scalar_t__ trailer_len; scalar_t__ header_len; scalar_t__ error; int /*<<< orphan*/  output; int /*<<< orphan*/  input; int /*<<< orphan*/ * xfrm; struct dst_ops* ops; struct net_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  metrics; } ;

/* Variables and functions */
 unsigned short DST_NOCOUNT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 TYPE_1__ dst_default_metrics ; 
 int /*<<< orphan*/  dst_discard ; 
 int /*<<< orphan*/  dst_discard_out ; 
 int /*<<< orphan*/  dst_entries_add (struct dst_ops*,int) ; 
 int /*<<< orphan*/  dst_init_metrics (struct dst_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jiffies ; 

void dst_init(struct dst_entry *dst, struct dst_ops *ops,
	      struct net_device *dev, int initial_ref, int initial_obsolete,
	      unsigned short flags)
{
	dst->dev = dev;
	if (dev)
		dev_hold(dev);
	dst->ops = ops;
	dst_init_metrics(dst, dst_default_metrics.metrics, true);
	dst->expires = 0UL;
#ifdef CONFIG_XFRM
	dst->xfrm = NULL;
#endif
	dst->input = dst_discard;
	dst->output = dst_discard_out;
	dst->error = 0;
	dst->obsolete = initial_obsolete;
	dst->header_len = 0;
	dst->trailer_len = 0;
#ifdef CONFIG_IP_ROUTE_CLASSID
	dst->tclassid = 0;
#endif
	dst->lwtstate = NULL;
	atomic_set(&dst->__refcnt, initial_ref);
	dst->__use = 0;
	dst->lastuse = jiffies;
	dst->flags = flags;
	if (!(flags & DST_NOCOUNT))
		dst_entries_add(ops, 1);
}