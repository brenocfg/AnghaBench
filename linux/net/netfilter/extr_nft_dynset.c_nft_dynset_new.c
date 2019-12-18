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
typedef  int /*<<< orphan*/  u64 ;
struct nft_set_ext {int dummy; } ;
struct nft_set {int /*<<< orphan*/  nelems; scalar_t__ size; int /*<<< orphan*/  timeout; } ;
struct nft_regs {int /*<<< orphan*/ * data; } ;
struct nft_expr {int dummy; } ;
struct nft_dynset {size_t sreg_key; size_t sreg_data; int /*<<< orphan*/ * expr; int /*<<< orphan*/  tmpl; scalar_t__ timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ nft_expr_clone (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nft_dynset* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_set_elem_destroy (struct nft_set*,void*,int) ; 
 struct nft_set_ext* nft_set_elem_ext (struct nft_set*,void*) ; 
 void* nft_set_elem_init (struct nft_set*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_set_ext_expr (struct nft_set_ext*) ; 

__attribute__((used)) static void *nft_dynset_new(struct nft_set *set, const struct nft_expr *expr,
			    struct nft_regs *regs)
{
	const struct nft_dynset *priv = nft_expr_priv(expr);
	struct nft_set_ext *ext;
	u64 timeout;
	void *elem;

	if (!atomic_add_unless(&set->nelems, 1, set->size))
		return NULL;

	timeout = priv->timeout ? : set->timeout;
	elem = nft_set_elem_init(set, &priv->tmpl,
				 &regs->data[priv->sreg_key],
				 &regs->data[priv->sreg_data],
				 timeout, 0, GFP_ATOMIC);
	if (elem == NULL)
		goto err1;

	ext = nft_set_elem_ext(set, elem);
	if (priv->expr != NULL &&
	    nft_expr_clone(nft_set_ext_expr(ext), priv->expr) < 0)
		goto err2;

	return elem;

err2:
	nft_set_elem_destroy(set, elem, false);
err1:
	if (set->size)
		atomic_dec(&set->nelems);
	return NULL;
}