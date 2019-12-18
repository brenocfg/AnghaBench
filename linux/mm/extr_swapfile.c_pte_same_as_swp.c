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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int pte_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_swp_clear_soft_dirty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int pte_same_as_swp(pte_t pte, pte_t swp_pte)
{
	return pte_same(pte_swp_clear_soft_dirty(pte), swp_pte);
}