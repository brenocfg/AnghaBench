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
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct TYPE_8__ {int saddr; int daddr; int proto; int mode; int spi; int reqid; } ;
struct TYPE_6__ {int /*<<< orphan*/  reqid; int /*<<< orphan*/  spi; int /*<<< orphan*/  mode; int /*<<< orphan*/  proto; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct xt_policy_elem {scalar_t__ proto; scalar_t__ mode; scalar_t__ spi; scalar_t__ reqid; TYPE_4__ invert; TYPE_2__ match; int /*<<< orphan*/  dmask; int /*<<< orphan*/  daddr; int /*<<< orphan*/  smask; int /*<<< orphan*/  saddr; } ;
struct TYPE_7__ {scalar_t__ mode; scalar_t__ reqid; int /*<<< orphan*/  saddr; } ;
struct TYPE_5__ {scalar_t__ proto; scalar_t__ spi; int /*<<< orphan*/  daddr; } ;
struct xfrm_state {TYPE_3__ props; TYPE_1__ id; } ;

/* Variables and functions */
 int xt_addr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,union nf_inet_addr const*,unsigned short) ; 

__attribute__((used)) static bool
match_xfrm_state(const struct xfrm_state *x, const struct xt_policy_elem *e,
		 unsigned short family)
{
#define MATCH_ADDR(x,y,z)	(!e->match.x ||			       \
				 (xt_addr_cmp(&e->x, &e->y, (const union nf_inet_addr *)(z), family) \
				  ^ e->invert.x))
#define MATCH(x,y)		(!e->match.x || ((e->x == (y)) ^ e->invert.x))

	return MATCH_ADDR(saddr, smask, &x->props.saddr) &&
	       MATCH_ADDR(daddr, dmask, &x->id.daddr) &&
	       MATCH(proto, x->id.proto) &&
	       MATCH(mode, x->props.mode) &&
	       MATCH(spi, x->id.spi) &&
	       MATCH(reqid, x->props.reqid);
}