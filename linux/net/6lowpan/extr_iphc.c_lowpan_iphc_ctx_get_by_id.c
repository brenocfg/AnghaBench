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
typedef  size_t u8 ;
struct net_device {int dummy; } ;
struct lowpan_iphc_ctx {int dummy; } ;
struct TYPE_3__ {struct lowpan_iphc_ctx* table; } ;
struct TYPE_4__ {TYPE_1__ ctx; } ;

/* Variables and functions */
 TYPE_2__* lowpan_dev (struct net_device const*) ; 
 int /*<<< orphan*/  lowpan_iphc_ctx_is_active (struct lowpan_iphc_ctx*) ; 

__attribute__((used)) static struct lowpan_iphc_ctx *
lowpan_iphc_ctx_get_by_id(const struct net_device *dev, u8 id)
{
	struct lowpan_iphc_ctx *ret = &lowpan_dev(dev)->ctx.table[id];

	if (!lowpan_iphc_ctx_is_active(ret))
		return NULL;

	return ret;
}