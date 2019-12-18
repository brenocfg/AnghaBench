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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t PAGE_MASK ; 
 size_t PAGE_SHIFT ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 char* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 

__attribute__((used)) static void
_shift_data_right_pages(struct page **pages, size_t pgto_base,
		size_t pgfrom_base, size_t len)
{
	struct page **pgfrom, **pgto;
	char *vfrom, *vto;
	size_t copy;

	BUG_ON(pgto_base <= pgfrom_base);

	pgto_base += len;
	pgfrom_base += len;

	pgto = pages + (pgto_base >> PAGE_SHIFT);
	pgfrom = pages + (pgfrom_base >> PAGE_SHIFT);

	pgto_base &= ~PAGE_MASK;
	pgfrom_base &= ~PAGE_MASK;

	do {
		/* Are any pointers crossing a page boundary? */
		if (pgto_base == 0) {
			pgto_base = PAGE_SIZE;
			pgto--;
		}
		if (pgfrom_base == 0) {
			pgfrom_base = PAGE_SIZE;
			pgfrom--;
		}

		copy = len;
		if (copy > pgto_base)
			copy = pgto_base;
		if (copy > pgfrom_base)
			copy = pgfrom_base;
		pgto_base -= copy;
		pgfrom_base -= copy;

		vto = kmap_atomic(*pgto);
		if (*pgto != *pgfrom) {
			vfrom = kmap_atomic(*pgfrom);
			memcpy(vto + pgto_base, vfrom + pgfrom_base, copy);
			kunmap_atomic(vfrom);
		} else
			memmove(vto + pgto_base, vto + pgfrom_base, copy);
		flush_dcache_page(*pgto);
		kunmap_atomic(vto);

	} while ((len -= copy) != 0);
}