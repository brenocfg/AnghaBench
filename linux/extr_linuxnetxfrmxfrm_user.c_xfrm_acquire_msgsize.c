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
struct xfrm_user_tmpl {int dummy; } ;
struct xfrm_user_acquire {int dummy; } ;
struct xfrm_state {int /*<<< orphan*/  security; } ;
struct xfrm_policy {int xfrm_nr; } ;
struct xfrm_mark {int dummy; } ;

/* Variables and functions */
 unsigned int NLMSG_ALIGN (int) ; 
 unsigned int nla_total_size (int) ; 
 unsigned int userpolicy_type_attrsize () ; 
 int xfrm_user_sec_ctx_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int xfrm_acquire_msgsize(struct xfrm_state *x,
						struct xfrm_policy *xp)
{
	return NLMSG_ALIGN(sizeof(struct xfrm_user_acquire))
	       + nla_total_size(sizeof(struct xfrm_user_tmpl) * xp->xfrm_nr)
	       + nla_total_size(sizeof(struct xfrm_mark))
	       + nla_total_size(xfrm_user_sec_ctx_size(x->security))
	       + userpolicy_type_attrsize();
}