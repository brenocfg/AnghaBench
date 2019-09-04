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
struct TYPE_4__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  len; } ;
struct TYPE_5__ {TYPE_1__ bin_val; } ;
struct team_gsetter_ctx {TYPE_2__ data; } ;
struct team {int /*<<< orphan*/  lock; } ;
struct sock_fprog_kern {int dummy; } ;
struct lb_priv {TYPE_3__* ex; int /*<<< orphan*/  fp; } ;
struct bpf_prog {int dummy; } ;
struct TYPE_6__ {struct sock_fprog_kern* orig_fprog; } ;

/* Variables and functions */
 int __fprog_create (struct sock_fprog_kern**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __fprog_destroy (struct sock_fprog_kern*) ; 
 int bpf_prog_create (struct bpf_prog**,struct sock_fprog_kern*) ; 
 int /*<<< orphan*/  bpf_prog_destroy (struct bpf_prog*) ; 
 struct lb_priv* get_lb_priv (struct team*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct bpf_prog*) ; 
 struct bpf_prog* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static int lb_bpf_func_set(struct team *team, struct team_gsetter_ctx *ctx)
{
	struct lb_priv *lb_priv = get_lb_priv(team);
	struct bpf_prog *fp = NULL;
	struct bpf_prog *orig_fp = NULL;
	struct sock_fprog_kern *fprog = NULL;
	int err;

	if (ctx->data.bin_val.len) {
		err = __fprog_create(&fprog, ctx->data.bin_val.len,
				     ctx->data.bin_val.ptr);
		if (err)
			return err;
		err = bpf_prog_create(&fp, fprog);
		if (err) {
			__fprog_destroy(fprog);
			return err;
		}
	}

	if (lb_priv->ex->orig_fprog) {
		/* Clear old filter data */
		__fprog_destroy(lb_priv->ex->orig_fprog);
		orig_fp = rcu_dereference_protected(lb_priv->fp,
						lockdep_is_held(&team->lock));
	}

	rcu_assign_pointer(lb_priv->fp, fp);
	lb_priv->ex->orig_fprog = fprog;

	if (orig_fp) {
		synchronize_rcu();
		bpf_prog_destroy(orig_fp);
	}
	return 0;
}