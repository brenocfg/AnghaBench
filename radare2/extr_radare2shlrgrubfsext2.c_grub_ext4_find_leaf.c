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
struct grub_ext4_extent_idx {int /*<<< orphan*/  leaf; int /*<<< orphan*/  leaf_hi; int /*<<< orphan*/  block; } ;
struct grub_ext4_extent_header {scalar_t__ depth; int /*<<< orphan*/  entries; int /*<<< orphan*/  magic; } ;
struct grub_ext2_data {int /*<<< orphan*/  disk; } ;
typedef  int grub_uint32_t ;
typedef  int grub_disk_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_BLOCK_SIZE (struct grub_ext2_data*) ; 
 int EXT4_EXT_MAGIC ; 
 int LOG2_EXT2_BLOCK_SIZE (struct grub_ext2_data*) ; 
 scalar_t__ grub_disk_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int grub_le_to_cpu16 (int /*<<< orphan*/ ) ; 
 int grub_le_to_cpu32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct grub_ext4_extent_header *
grub_ext4_find_leaf (struct grub_ext2_data *data, char *buf,
                     struct grub_ext4_extent_header *ext_block,
                     grub_uint32_t fileblock)
{
  struct grub_ext4_extent_idx *index;

  while (1)
    {
      int i;
      grub_disk_addr_t block;

      index = (struct grub_ext4_extent_idx *) (ext_block + 1);

      if (grub_le_to_cpu16(ext_block->magic) != EXT4_EXT_MAGIC)
        return 0;

      if (ext_block->depth == 0)
        return ext_block;

      for (i = 0; i < grub_le_to_cpu16 (ext_block->entries); i++)
        {
          if (fileblock < grub_le_to_cpu32(index[i].block))
            break;
        }

      if (--i < 0)
        return 0;

      block = grub_le_to_cpu16 (index[i].leaf_hi);
      block = (block << 32) + grub_le_to_cpu32 (index[i].leaf);
      if (grub_disk_read (data->disk,
                          block << LOG2_EXT2_BLOCK_SIZE (data),
                          0, EXT2_BLOCK_SIZE(data), buf)) {
        return 0;
      }

      ext_block = (struct grub_ext4_extent_header *) buf;
    }
}