#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ a4; } ;
typedef  TYPE_5__ xfrm_address_t ;
struct TYPE_10__ {scalar_t__ a4; } ;
struct TYPE_8__ {scalar_t__ a4; } ;
struct TYPE_9__ {TYPE_1__ daddr; } ;
struct xfrm_tmpl {int /*<<< orphan*/  reqid; int /*<<< orphan*/  mode; TYPE_3__ saddr; TYPE_2__ id; } ;
struct TYPE_11__ {int /*<<< orphan*/  family; int /*<<< orphan*/  reqid; int /*<<< orphan*/  mode; TYPE_3__ saddr; } ;
struct xfrm_state {TYPE_4__ props; TYPE_2__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 

__attribute__((used)) static void
xfrm4_init_temprop(struct xfrm_state *x, const struct xfrm_tmpl *tmpl,
		   const xfrm_address_t *daddr, const xfrm_address_t *saddr)
{
	x->id = tmpl->id;
	if (x->id.daddr.a4 == 0)
		x->id.daddr.a4 = daddr->a4;
	x->props.saddr = tmpl->saddr;
	if (x->props.saddr.a4 == 0)
		x->props.saddr.a4 = saddr->a4;
	x->props.mode = tmpl->mode;
	x->props.reqid = tmpl->reqid;
	x->props.family = AF_INET;
}