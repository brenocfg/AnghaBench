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
struct region {int end; unsigned int start; int /*<<< orphan*/  off; scalar_t__ group_len; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  bitmap_set (unsigned long*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bitmap_set_region(const struct region *r,
				unsigned long *bitmap, int nbits)
{
	unsigned int start;

	if (r->end >= nbits)
		return -ERANGE;

	for (start = r->start; start <= r->end; start += r->group_len)
		bitmap_set(bitmap, start, min(r->end - start + 1, r->off));

	return 0;
}