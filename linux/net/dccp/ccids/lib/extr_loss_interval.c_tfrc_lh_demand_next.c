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
struct tfrc_loss_interval {int dummy; } ;
struct tfrc_loss_hist {int /*<<< orphan*/  counter; struct tfrc_loss_interval** ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 size_t LIH_INDEX (int /*<<< orphan*/ ) ; 
 struct tfrc_loss_interval* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfrc_lh_slab ; 

__attribute__((used)) static struct tfrc_loss_interval *tfrc_lh_demand_next(struct tfrc_loss_hist *lh)
{
	if (lh->ring[LIH_INDEX(lh->counter)] == NULL)
		lh->ring[LIH_INDEX(lh->counter)] = kmem_cache_alloc(tfrc_lh_slab,
								    GFP_ATOMIC);
	return lh->ring[LIH_INDEX(lh->counter)];
}