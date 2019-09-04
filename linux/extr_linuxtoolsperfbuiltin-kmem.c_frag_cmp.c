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
struct alloc_stat {int /*<<< orphan*/  bytes_alloc; int /*<<< orphan*/  bytes_req; } ;

/* Variables and functions */
 double fragmentation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int frag_cmp(void *a, void *b)
{
	double x, y;
	struct alloc_stat *l = a;
	struct alloc_stat *r = b;

	x = fragmentation(l->bytes_req, l->bytes_alloc);
	y = fragmentation(r->bytes_req, r->bytes_alloc);

	if (x < y)
		return -1;
	else if (x > y)
		return 1;
	return 0;
}