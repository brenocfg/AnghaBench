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
struct typec_altmode {int /*<<< orphan*/  dev; } ;
struct notifier_block {int dummy; } ;
struct altmode {int /*<<< orphan*/  nh; } ;

/* Variables and functions */
 int /*<<< orphan*/  blocking_notifier_chain_unregister (int /*<<< orphan*/ *,struct notifier_block*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct altmode* to_altmode (struct typec_altmode*) ; 

void typec_altmode_unregister_notifier(struct typec_altmode *adev,
				       struct notifier_block *nb)
{
	struct altmode *altmode = to_altmode(adev);

	blocking_notifier_chain_unregister(&altmode->nh, nb);
	put_device(&adev->dev);
}