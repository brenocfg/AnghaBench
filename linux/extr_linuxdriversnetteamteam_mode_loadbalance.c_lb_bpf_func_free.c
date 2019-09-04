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
struct team {int /*<<< orphan*/  lock; } ;
struct lb_priv {int /*<<< orphan*/  fp; TYPE_1__* ex; } ;
struct bpf_prog {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  orig_fprog; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fprog_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_destroy (struct bpf_prog*) ; 
 struct lb_priv* get_lb_priv (struct team*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct bpf_prog* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lb_bpf_func_free(struct team *team)
{
	struct lb_priv *lb_priv = get_lb_priv(team);
	struct bpf_prog *fp;

	if (!lb_priv->ex->orig_fprog)
		return;

	__fprog_destroy(lb_priv->ex->orig_fprog);
	fp = rcu_dereference_protected(lb_priv->fp,
				       lockdep_is_held(&team->lock));
	bpf_prog_destroy(fp);
}