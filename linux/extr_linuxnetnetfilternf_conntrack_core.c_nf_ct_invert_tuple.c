#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  all; } ;
struct TYPE_8__ {int /*<<< orphan*/  in6; int /*<<< orphan*/  ip; } ;
struct TYPE_12__ {int l3num; TYPE_5__ u; TYPE_2__ u3; } ;
struct TYPE_9__ {int /*<<< orphan*/  all; } ;
struct TYPE_7__ {int /*<<< orphan*/  in6; int /*<<< orphan*/  ip; } ;
struct TYPE_10__ {int dir; TYPE_3__ u; int /*<<< orphan*/  protonum; TYPE_1__ u3; } ;
struct nf_conntrack_tuple {TYPE_6__ src; TYPE_4__ dst; } ;
struct nf_conntrack_l4proto {int (* invert_tuple ) (struct nf_conntrack_tuple*,struct nf_conntrack_tuple const*) ;} ;

/* Variables and functions */
#define  NFPROTO_IPV4 129 
#define  NFPROTO_IPV6 128 
 int /*<<< orphan*/  memset (struct nf_conntrack_tuple*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct nf_conntrack_tuple*,struct nf_conntrack_tuple const*) ; 
 scalar_t__ unlikely (int (*) (struct nf_conntrack_tuple*,struct nf_conntrack_tuple const*)) ; 

bool
nf_ct_invert_tuple(struct nf_conntrack_tuple *inverse,
		   const struct nf_conntrack_tuple *orig,
		   const struct nf_conntrack_l4proto *l4proto)
{
	memset(inverse, 0, sizeof(*inverse));

	inverse->src.l3num = orig->src.l3num;

	switch (orig->src.l3num) {
	case NFPROTO_IPV4:
		inverse->src.u3.ip = orig->dst.u3.ip;
		inverse->dst.u3.ip = orig->src.u3.ip;
		break;
	case NFPROTO_IPV6:
		inverse->src.u3.in6 = orig->dst.u3.in6;
		inverse->dst.u3.in6 = orig->src.u3.in6;
		break;
	default:
		break;
	}

	inverse->dst.dir = !orig->dst.dir;

	inverse->dst.protonum = orig->dst.protonum;

	if (unlikely(l4proto->invert_tuple))
		return l4proto->invert_tuple(inverse, orig);

	inverse->src.u.all = orig->dst.u.all;
	inverse->dst.u.all = orig->src.u.all;
	return true;
}