#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_7__ {scalar_t__ all; } ;
struct TYPE_8__ {TYPE_3__ u; } ;
struct TYPE_5__ {scalar_t__ all; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
struct nf_conntrack_tuple {TYPE_4__ dst; TYPE_2__ src; } ;
struct net {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool generic_pkt_to_tuple(const struct sk_buff *skb,
				 unsigned int dataoff,
				 struct net *net, struct nf_conntrack_tuple *tuple)
{
	tuple->src.u.all = 0;
	tuple->dst.u.all = 0;

	return true;
}