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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  kasan_early_shadow_pte ; 
 int /*<<< orphan*/  lm_alias (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_page (int /*<<< orphan*/ ) ; 
 scalar_t__ virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool kasan_pte_table(pmd_t pmd)
{
	return pmd_page(pmd) == virt_to_page(lm_alias(kasan_early_shadow_pte));
}