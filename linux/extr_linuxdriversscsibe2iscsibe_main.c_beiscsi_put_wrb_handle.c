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
struct wrb_handle {int /*<<< orphan*/ * pio_handle; } ;
struct hwi_wrb_context {size_t free_index; int /*<<< orphan*/  wrb_lock; int /*<<< orphan*/  wrb_handles_available; struct wrb_handle** pwrb_handle_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void
beiscsi_put_wrb_handle(struct hwi_wrb_context *pwrb_context,
		       struct wrb_handle *pwrb_handle,
		       unsigned int wrbs_per_cxn)
{
	unsigned long flags;

	spin_lock_irqsave(&pwrb_context->wrb_lock, flags);
	pwrb_context->pwrb_handle_base[pwrb_context->free_index] = pwrb_handle;
	pwrb_context->wrb_handles_available++;
	if (pwrb_context->free_index == (wrbs_per_cxn - 1))
		pwrb_context->free_index = 0;
	else
		pwrb_context->free_index++;
	pwrb_handle->pio_handle = NULL;
	spin_unlock_irqrestore(&pwrb_context->wrb_lock, flags);
}