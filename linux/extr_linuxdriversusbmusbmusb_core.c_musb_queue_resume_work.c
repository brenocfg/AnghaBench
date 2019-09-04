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
struct musb_pending_work {int (* callback ) (struct musb*,void*) ;int /*<<< orphan*/  node; void* data; } ;
struct musb {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  controller; int /*<<< orphan*/  pending_list; scalar_t__ is_runtime_suspended; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int (*) (struct musb*,void*)) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct musb_pending_work*) ; 
 struct musb_pending_work* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pm_runtime_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int musb_queue_resume_work(struct musb *musb,
			   int (*callback)(struct musb *musb, void *data),
			   void *data)
{
	struct musb_pending_work *w;
	unsigned long flags;
	int error;

	if (WARN_ON(!callback))
		return -EINVAL;

	if (pm_runtime_active(musb->controller))
		return callback(musb, data);

	w = devm_kzalloc(musb->controller, sizeof(*w), GFP_ATOMIC);
	if (!w)
		return -ENOMEM;

	w->callback = callback;
	w->data = data;
	spin_lock_irqsave(&musb->list_lock, flags);
	if (musb->is_runtime_suspended) {
		list_add_tail(&w->node, &musb->pending_list);
		error = 0;
	} else {
		dev_err(musb->controller, "could not add resume work %p\n",
			callback);
		devm_kfree(musb->controller, w);
		error = -EINPROGRESS;
	}
	spin_unlock_irqrestore(&musb->list_lock, flags);

	return error;
}