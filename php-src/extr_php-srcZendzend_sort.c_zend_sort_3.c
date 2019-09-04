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
typedef  int /*<<< orphan*/  (* swap_func_t ) (void*,void*) ;
typedef  scalar_t__ (* compare_func_t ) (void*,void*) ;

/* Variables and functions */

__attribute__((used)) static inline void zend_sort_3(void *a, void *b, void *c, compare_func_t cmp, swap_func_t swp) /* {{{ */ {
	if (!(cmp(a, b) > 0)) {
		if (!(cmp(b, c) > 0)) {
			return;
		}
		swp(b, c);
		if (cmp(a, b) > 0) {
			swp(a, b);
		}
		return;
	}
	if (!(cmp(c, b) > 0)) {
		swp(a, c);
		return;
	}
	swp(a, b);
	if (cmp(b, c) > 0) {
		swp(b, c);
	}
}