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
struct qcom_smem_state_ops {int dummy; } ;
struct qcom_smem_state {int /*<<< orphan*/  list; void* priv; struct qcom_smem_state_ops ops; struct device_node* of_node; int /*<<< orphan*/  refcount; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct qcom_smem_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct qcom_smem_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smem_states ; 

struct qcom_smem_state *qcom_smem_state_register(struct device_node *of_node,
						 const struct qcom_smem_state_ops *ops,
						 void *priv)
{
	struct qcom_smem_state *state;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		return ERR_PTR(-ENOMEM);

	kref_init(&state->refcount);

	state->of_node = of_node;
	state->ops = *ops;
	state->priv = priv;

	mutex_lock(&list_lock);
	list_add(&state->list, &smem_states);
	mutex_unlock(&list_lock);

	return state;
}