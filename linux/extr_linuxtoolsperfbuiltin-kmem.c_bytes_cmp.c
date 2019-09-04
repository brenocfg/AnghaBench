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
struct alloc_stat {scalar_t__ bytes_alloc; } ;

/* Variables and functions */

__attribute__((used)) static int bytes_cmp(void *a, void *b)
{
	struct alloc_stat *l = a;
	struct alloc_stat *r = b;

	if (l->bytes_alloc < r->bytes_alloc)
		return -1;
	else if (l->bytes_alloc > r->bytes_alloc)
		return 1;
	return 0;
}