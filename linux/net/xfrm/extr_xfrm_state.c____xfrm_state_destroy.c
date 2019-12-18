#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xfrm_state {TYPE_1__* type; scalar_t__ type_offload; int /*<<< orphan*/  preplay_esn; int /*<<< orphan*/  replay_esn; int /*<<< orphan*/  coaddr; int /*<<< orphan*/  encap; int /*<<< orphan*/  calg; int /*<<< orphan*/  ealg; int /*<<< orphan*/  aalg; int /*<<< orphan*/  aead; int /*<<< orphan*/  rtimer; int /*<<< orphan*/  mtimer; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destructor ) (struct xfrm_state*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_xfrm_state_free (struct xfrm_state*) ; 
 int /*<<< orphan*/  stub1 (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_dev_state_free (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_put_type (TYPE_1__*) ; 
 int /*<<< orphan*/  xfrm_put_type_offload (scalar_t__) ; 
 int /*<<< orphan*/  xfrm_state_free (struct xfrm_state*) ; 

__attribute__((used)) static void ___xfrm_state_destroy(struct xfrm_state *x)
{
	hrtimer_cancel(&x->mtimer);
	del_timer_sync(&x->rtimer);
	kfree(x->aead);
	kfree(x->aalg);
	kfree(x->ealg);
	kfree(x->calg);
	kfree(x->encap);
	kfree(x->coaddr);
	kfree(x->replay_esn);
	kfree(x->preplay_esn);
	if (x->type_offload)
		xfrm_put_type_offload(x->type_offload);
	if (x->type) {
		x->type->destructor(x);
		xfrm_put_type(x->type);
	}
	xfrm_dev_state_free(x);
	security_xfrm_state_free(x);
	xfrm_state_free(x);
}