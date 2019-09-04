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
typedef  int /*<<< orphan*/  u64 ;
struct extent_io_tree {int dummy; } ;

/* Variables and functions */
 unsigned int EXTENT_LOCKED ; 
 int clear_extent_bit (struct extent_io_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int clear_extent_bits(struct extent_io_tree *tree, u64 start,
		u64 end, unsigned bits)
{
	int wake = 0;

	if (bits & EXTENT_LOCKED)
		wake = 1;

	return clear_extent_bit(tree, start, end, bits, wake, 0, NULL);
}