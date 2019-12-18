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
struct grub_nilfs2_inode {int /*<<< orphan*/ * i_bmap; } ;
typedef  int grub_uint64_t ;

/* Variables and functions */
 int grub_le_to_cpu64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline grub_uint64_t
grub_nilfs2_direct_lookup (struct grub_nilfs2_inode *inode, grub_uint64_t key)
{
  return grub_le_to_cpu64 (inode->i_bmap[1 + key]);
}