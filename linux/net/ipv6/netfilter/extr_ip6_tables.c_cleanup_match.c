#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xt_mtdtor_param {TYPE_3__* match; int /*<<< orphan*/  family; int /*<<< orphan*/  matchinfo; struct net* net; } ;
struct TYPE_4__ {TYPE_3__* match; } ;
struct TYPE_5__ {TYPE_1__ kernel; } ;
struct xt_entry_match {int /*<<< orphan*/  data; TYPE_2__ u; } ;
struct net {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  me; int /*<<< orphan*/  (* destroy ) (struct xt_mtdtor_param*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NFPROTO_IPV6 ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xt_mtdtor_param*) ; 

__attribute__((used)) static void cleanup_match(struct xt_entry_match *m, struct net *net)
{
	struct xt_mtdtor_param par;

	par.net       = net;
	par.match     = m->u.kernel.match;
	par.matchinfo = m->data;
	par.family    = NFPROTO_IPV6;
	if (par.match->destroy != NULL)
		par.match->destroy(&par);
	module_put(par.match->me);
}