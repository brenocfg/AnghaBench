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
struct flow_indr_block_dev {int /*<<< orphan*/  cb_list; } ;
struct flow_indr_block_cb {int /*<<< orphan*/  list; void* cb_ident; int /*<<< orphan*/ * cb; void* cb_priv; } ;
typedef  int /*<<< orphan*/  flow_indr_block_bind_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct flow_indr_block_cb* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct flow_indr_block_cb* flow_indr_block_cb_lookup (struct flow_indr_block_dev*,int /*<<< orphan*/ *,void*) ; 
 struct flow_indr_block_cb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct flow_indr_block_cb *
flow_indr_block_cb_add(struct flow_indr_block_dev *indr_dev, void *cb_priv,
		       flow_indr_block_bind_cb_t *cb, void *cb_ident)
{
	struct flow_indr_block_cb *indr_block_cb;

	indr_block_cb = flow_indr_block_cb_lookup(indr_dev, cb, cb_ident);
	if (indr_block_cb)
		return ERR_PTR(-EEXIST);

	indr_block_cb = kzalloc(sizeof(*indr_block_cb), GFP_KERNEL);
	if (!indr_block_cb)
		return ERR_PTR(-ENOMEM);

	indr_block_cb->cb_priv = cb_priv;
	indr_block_cb->cb = cb;
	indr_block_cb->cb_ident = cb_ident;
	list_add(&indr_block_cb->list, &indr_dev->cb_list);

	return indr_block_cb;
}