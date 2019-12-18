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
struct mm_walk {scalar_t__ private; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int EACCES ; 
 scalar_t__ pfn_modify_allowed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prot_none_hugetlb_entry(pte_t *pte, unsigned long hmask,
				   unsigned long addr, unsigned long next,
				   struct mm_walk *walk)
{
	return pfn_modify_allowed(pte_pfn(*pte), *(pgprot_t *)(walk->private)) ?
		0 : -EACCES;
}