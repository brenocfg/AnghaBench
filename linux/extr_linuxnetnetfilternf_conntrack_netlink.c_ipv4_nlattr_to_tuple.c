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
struct nlattr {int dummy; } ;
struct TYPE_7__ {void* ip; } ;
struct TYPE_8__ {TYPE_3__ u3; } ;
struct TYPE_5__ {void* ip; } ;
struct TYPE_6__ {TYPE_1__ u3; } ;
struct nf_conntrack_tuple {TYPE_4__ dst; TYPE_2__ src; } ;

/* Variables and functions */
 size_t CTA_IP_V4_DST ; 
 size_t CTA_IP_V4_SRC ; 
 int EINVAL ; 
 void* nla_get_in_addr (struct nlattr*) ; 

__attribute__((used)) static int ipv4_nlattr_to_tuple(struct nlattr *tb[],
				struct nf_conntrack_tuple *t)
{
	if (!tb[CTA_IP_V4_SRC] || !tb[CTA_IP_V4_DST])
		return -EINVAL;

	t->src.u3.ip = nla_get_in_addr(tb[CTA_IP_V4_SRC]);
	t->dst.u3.ip = nla_get_in_addr(tb[CTA_IP_V4_DST]);

	return 0;
}