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
struct resource {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PHYS_PFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgmap_array ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  xa_store_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pgmap_array_delete(struct resource *res)
{
	xa_store_range(&pgmap_array, PHYS_PFN(res->start), PHYS_PFN(res->end),
			NULL, GFP_KERNEL);
	synchronize_rcu();
}