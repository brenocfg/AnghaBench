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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 void* krealloc (void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static
int i2400m_zrealloc_2x(void **ptr, size_t *_count, size_t el_size,
		       gfp_t gfp_flags)
{
	size_t old_count = *_count,
		new_count = old_count ? 2 * old_count : 2,
		old_size = el_size * old_count,
		new_size = el_size * new_count;
	void *nptr = krealloc(*ptr, new_size, gfp_flags);
	if (nptr) {
		/* zero the other half or the whole thing if old_count
		 * was zero */
		if (old_size == 0)
			memset(nptr, 0, new_size);
		else
			memset(nptr + old_size, 0, old_size);
		*_count = new_count;
		*ptr = nptr;
		return 0;
	} else
		return -ENOMEM;
}