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
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  init_mm ; 
 unsigned long p4d_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * p4d_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ vmap_pud_range (int /*<<< orphan*/ *,unsigned long,unsigned long,int /*<<< orphan*/ ,struct page**,int*) ; 

__attribute__((used)) static int vmap_p4d_range(pgd_t *pgd, unsigned long addr,
		unsigned long end, pgprot_t prot, struct page **pages, int *nr)
{
	p4d_t *p4d;
	unsigned long next;

	p4d = p4d_alloc(&init_mm, pgd, addr);
	if (!p4d)
		return -ENOMEM;
	do {
		next = p4d_addr_end(addr, end);
		if (vmap_pud_range(p4d, addr, next, prot, pages, nr))
			return -ENOMEM;
	} while (p4d++, addr = next, addr != end);
	return 0;
}