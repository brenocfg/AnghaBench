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
struct btrfsic_dev_state {scalar_t__ magic_num; } ;

/* Variables and functions */
 scalar_t__ BTRFSIC_DEV2STATE_MAGIC_NUMBER ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  kfree (struct btrfsic_dev_state*) ; 

__attribute__((used)) static void btrfsic_dev_state_free(struct btrfsic_dev_state *ds)
{
	BUG_ON(!(NULL == ds ||
		 BTRFSIC_DEV2STATE_MAGIC_NUMBER == ds->magic_num));
	kfree(ds);
}