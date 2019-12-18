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
struct buffer_head {int /*<<< orphan*/  b_page; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_MAGIC ; 
 int bh_offset (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_escaped (struct buffer_head*) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  set_buffer_escaped (struct buffer_head*) ; 

__attribute__((used)) static void gfs2_check_magic(struct buffer_head *bh)
{
	void *kaddr;
	__be32 *ptr;

	clear_buffer_escaped(bh);
	kaddr = kmap_atomic(bh->b_page);
	ptr = kaddr + bh_offset(bh);
	if (*ptr == cpu_to_be32(GFS2_MAGIC))
		set_buffer_escaped(bh);
	kunmap_atomic(kaddr);
}