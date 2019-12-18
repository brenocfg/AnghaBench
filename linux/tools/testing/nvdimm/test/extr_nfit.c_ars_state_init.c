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
struct nd_cmd_ars_status {int dummy; } ;
struct device {int dummy; } ;
struct ars_state {int /*<<< orphan*/  lock; int /*<<< orphan*/  ars_status; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SZ_4K ; 
 int /*<<< orphan*/  devm_kzalloc (struct device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ars_state_init(struct device *dev, struct ars_state *ars_state)
{
	/* for testing, only store up to n records that fit within 4k */
	ars_state->ars_status = devm_kzalloc(dev,
			sizeof(struct nd_cmd_ars_status) + SZ_4K, GFP_KERNEL);
	if (!ars_state->ars_status)
		return -ENOMEM;
	spin_lock_init(&ars_state->lock);
	return 0;
}