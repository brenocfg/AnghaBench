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
struct ufs_hba {int is_irq_enabled; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ufs_hba*) ; 

__attribute__((used)) static inline void ufshcd_disable_irq(struct ufs_hba *hba)
{
	if (hba->is_irq_enabled) {
		free_irq(hba->irq, hba);
		hba->is_irq_enabled = false;
	}
}