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
struct hw20k2 {struct hw hw; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct hw ct20k2_preset ; 
 struct hw20k2* kzalloc (int,int /*<<< orphan*/ ) ; 

int create_20k2_hw_obj(struct hw **rhw)
{
	struct hw20k2 *hw20k2;

	*rhw = NULL;
	hw20k2 = kzalloc(sizeof(*hw20k2), GFP_KERNEL);
	if (!hw20k2)
		return -ENOMEM;

	hw20k2->hw = ct20k2_preset;
	*rhw = &hw20k2->hw;

	return 0;
}