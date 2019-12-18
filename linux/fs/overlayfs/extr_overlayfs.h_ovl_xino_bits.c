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
struct super_block {struct ovl_fs* s_fs_info; } ;
struct ovl_fs {unsigned int xino_bits; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int ovl_xino_bits(struct super_block *sb)
{
	struct ovl_fs *ofs = sb->s_fs_info;

	return ofs->xino_bits;
}