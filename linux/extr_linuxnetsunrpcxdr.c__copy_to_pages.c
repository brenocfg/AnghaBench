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
 size_t PAGE_MASK ; 
 size_t PAGE_SHIFT ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 char* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static void
_copy_to_pages(struct page **pages, size_t pgbase, const char *p, size_t len)
{
	struct page **pgto;
	char *vto;
	size_t copy;

	pgto = pages + (pgbase >> PAGE_SHIFT);
	pgbase &= ~PAGE_MASK;

	for (;;) {
		copy = PAGE_SIZE - pgbase;
		if (copy > len)
			copy = len;

		vto = kmap_atomic(*pgto);
		memcpy(vto + pgbase, p, copy);
		kunmap_atomic(vto);

		len -= copy;
		if (len == 0)
			break;

		pgbase += copy;
		if (pgbase == PAGE_SIZE) {
			flush_dcache_page(*pgto);
			pgbase = 0;
			pgto++;
		}
		p += copy;
	}
	flush_dcache_page(*pgto);
}