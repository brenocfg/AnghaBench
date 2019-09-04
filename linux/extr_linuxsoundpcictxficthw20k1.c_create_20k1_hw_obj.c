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
struct hw {int dummy; } ;
struct hw20k1 {struct hw hw; int /*<<< orphan*/  reg_pci_lock; int /*<<< orphan*/  reg_20k1_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct hw ct20k1_preset ; 
 struct hw20k1* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int create_20k1_hw_obj(struct hw **rhw)
{
	struct hw20k1 *hw20k1;

	*rhw = NULL;
	hw20k1 = kzalloc(sizeof(*hw20k1), GFP_KERNEL);
	if (!hw20k1)
		return -ENOMEM;

	spin_lock_init(&hw20k1->reg_20k1_lock);
	spin_lock_init(&hw20k1->reg_pci_lock);

	hw20k1->hw = ct20k1_preset;

	*rhw = &hw20k1->hw;

	return 0;
}