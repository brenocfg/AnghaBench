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
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ishst ; 

__attribute__((used)) static inline void kvm_set_pte(pte_t *ptep, pte_t new_pte)
{
	WRITE_ONCE(*ptep, new_pte);
	dsb(ishst);
}