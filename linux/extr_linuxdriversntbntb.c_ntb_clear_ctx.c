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
struct ntb_dev {int /*<<< orphan*/  ctx_lock; int /*<<< orphan*/ * ctx; int /*<<< orphan*/ * ctx_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ntb_clear_ctx(struct ntb_dev *ntb)
{
	unsigned long irqflags;

	spin_lock_irqsave(&ntb->ctx_lock, irqflags);
	{
		ntb->ctx_ops = NULL;
		ntb->ctx = NULL;
	}
	spin_unlock_irqrestore(&ntb->ctx_lock, irqflags);
}