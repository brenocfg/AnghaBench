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
struct fpm_array_s {int used; int /*<<< orphan*/  sz; } ;

/* Variables and functions */
 void* fpm_array_item (struct fpm_array_s*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int fpm_array_item_remove(struct fpm_array_s *a, unsigned int n) /* {{{ */
{
	int ret = -1;

	if (n < a->used - 1) {
		void *last = fpm_array_item(a, a->used - 1);
		void *to_remove = fpm_array_item(a, n);

		memcpy(to_remove, last, a->sz);

		ret = n;
	}

	--a->used;

	return ret;
}