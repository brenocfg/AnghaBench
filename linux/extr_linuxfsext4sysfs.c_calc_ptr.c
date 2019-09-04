#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ext4_sb_info {scalar_t__ s_es; } ;
struct TYPE_2__ {void* explicit_ptr; int /*<<< orphan*/  offset; } ;
struct ext4_attr {int attr_ptr; TYPE_1__ u; } ;

/* Variables and functions */
#define  ptr_explicit 130 
#define  ptr_ext4_sb_info_offset 129 
#define  ptr_ext4_super_block_offset 128 

__attribute__((used)) static void *calc_ptr(struct ext4_attr *a, struct ext4_sb_info *sbi)
{
	switch (a->attr_ptr) {
	case ptr_explicit:
		return a->u.explicit_ptr;
	case ptr_ext4_sb_info_offset:
		return (void *) (((char *) sbi) + a->u.offset);
	case ptr_ext4_super_block_offset:
		return (void *) (((char *) sbi->s_es) + a->u.offset);
	}
	return NULL;
}