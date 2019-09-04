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
struct wilc_vif {int dummy; } ;
struct host_if_msg {void (* fn ) (struct work_struct*) ;int is_sync; int /*<<< orphan*/  work_comp; struct wilc_vif* vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct host_if_msg* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct host_if_msg* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct host_if_msg*
wilc_alloc_work(struct wilc_vif *vif, void (*work_fun)(struct work_struct *),
		bool is_sync)
{
	struct host_if_msg *msg;

	if (!work_fun)
		return ERR_PTR(-EINVAL);

	msg = kzalloc(sizeof(*msg), GFP_ATOMIC);
	if (!msg)
		return ERR_PTR(-ENOMEM);
	msg->fn = work_fun;
	msg->vif = vif;
	msg->is_sync = is_sync;
	if (is_sync)
		init_completion(&msg->work_comp);

	return msg;
}