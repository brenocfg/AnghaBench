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
 unsigned short PAGE_SIZE ; 
 char* kmap_atomic (struct page* const) ; 
 int /*<<< orphan*/  kunmap_atomic (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,unsigned int const,int) ; 
 int /*<<< orphan*/  uint ; 

__attribute__((used)) static void copy_from_pcpubuf(struct page **out, const char *dst,
			      unsigned short pageofs_out,
			      unsigned int outputsize)
{
	const char *end = dst + outputsize;
	const unsigned int righthalf = PAGE_SIZE - pageofs_out;
	const char *cur = dst - pageofs_out;

	while (cur < end) {
		struct page *const page = *out++;

		if (page) {
			char *buf = kmap_atomic(page);

			if (cur >= dst) {
				memcpy(buf, cur, min_t(uint, PAGE_SIZE,
						       end - cur));
			} else {
				memcpy(buf + pageofs_out, cur + pageofs_out,
				       min_t(uint, righthalf, end - cur));
			}
			kunmap_atomic(buf);
		}
		cur += PAGE_SIZE;
	}
}