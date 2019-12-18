#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sock {int dummy; } ;
struct lp {int owd_min; scalar_t__ inference; scalar_t__ last_drop; scalar_t__ local_ref_time; scalar_t__ remote_ref_time; scalar_t__ remote_hz; scalar_t__ owd_max_rsv; scalar_t__ owd_max; scalar_t__ sowd; scalar_t__ flag; } ;

/* Variables and functions */
 struct lp* inet_csk_ca (struct sock*) ; 

__attribute__((used)) static void tcp_lp_init(struct sock *sk)
{
	struct lp *lp = inet_csk_ca(sk);

	lp->flag = 0;
	lp->sowd = 0;
	lp->owd_min = 0xffffffff;
	lp->owd_max = 0;
	lp->owd_max_rsv = 0;
	lp->remote_hz = 0;
	lp->remote_ref_time = 0;
	lp->local_ref_time = 0;
	lp->last_drop = 0;
	lp->inference = 0;
}