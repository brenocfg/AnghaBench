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
struct ci_hdrc {int /*<<< orphan*/  irq; int /*<<< orphan*/  work; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ci_otg_queue_work(struct ci_hdrc *ci)
{
	disable_irq_nosync(ci->irq);
	if (queue_work(ci->wq, &ci->work) == false)
		enable_irq(ci->irq);
}