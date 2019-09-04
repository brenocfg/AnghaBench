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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_fn_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int ENOMEM ; 
 int apply_to_pud_range (struct mm_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long,int /*<<< orphan*/ ,void*) ; 
 unsigned long p4d_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * p4d_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int apply_to_p4d_range(struct mm_struct *mm, pgd_t *pgd,
				     unsigned long addr, unsigned long end,
				     pte_fn_t fn, void *data)
{
	p4d_t *p4d;
	unsigned long next;
	int err;

	p4d = p4d_alloc(mm, pgd, addr);
	if (!p4d)
		return -ENOMEM;
	do {
		next = p4d_addr_end(addr, end);
		err = apply_to_pud_range(mm, p4d, addr, next, fn, data);
		if (err)
			break;
	} while (p4d++, addr = next, addr != end);
	return err;
}