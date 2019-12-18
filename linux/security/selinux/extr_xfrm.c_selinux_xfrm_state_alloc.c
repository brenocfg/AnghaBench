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
struct xfrm_user_sec_ctx {int dummy; } ;
struct xfrm_state {int /*<<< orphan*/  security; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int selinux_xfrm_alloc_user (int /*<<< orphan*/ *,struct xfrm_user_sec_ctx*,int /*<<< orphan*/ ) ; 

int selinux_xfrm_state_alloc(struct xfrm_state *x,
			     struct xfrm_user_sec_ctx *uctx)
{
	return selinux_xfrm_alloc_user(&x->security, uctx, GFP_KERNEL);
}