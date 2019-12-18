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
typedef  int /*<<< orphan*/  u32 ;
struct aa_label {int dummy; } ;
struct aa_file_ctx {int /*<<< orphan*/  lock; int /*<<< orphan*/  allow; int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct aa_label* aa_label_merge (struct aa_label*,struct aa_label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct aa_label*) ; 
 struct aa_label* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_file_ctx(struct aa_file_ctx *fctx, struct aa_label *label,
			    u32 request)
{
	struct aa_label *l, *old;

	/* update caching of label on file_ctx */
	spin_lock(&fctx->lock);
	old = rcu_dereference_protected(fctx->label,
					lockdep_is_held(&fctx->lock));
	l = aa_label_merge(old, label, GFP_ATOMIC);
	if (l) {
		if (l != old) {
			rcu_assign_pointer(fctx->label, l);
			aa_put_label(old);
		} else
			aa_put_label(l);
		fctx->allow |= request;
	}
	spin_unlock(&fctx->lock);
}