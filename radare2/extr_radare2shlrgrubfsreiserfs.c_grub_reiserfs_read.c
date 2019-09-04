#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ offset_type; } ;
struct TYPE_12__ {TYPE_3__ v2; } ;
struct grub_reiserfs_key {TYPE_4__ u; int /*<<< orphan*/  object_id; int /*<<< orphan*/  directory_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  block_size; } ;
struct grub_reiserfs_data {TYPE_8__* disk; TYPE_1__ superblock; } ;
struct TYPE_10__ {int /*<<< orphan*/  object_id; int /*<<< orphan*/  directory_id; } ;
struct TYPE_13__ {int /*<<< orphan*/  item_location; int /*<<< orphan*/  item_size; TYPE_2__ key; } ;
struct grub_fshelp_node {scalar_t__ block_number; int type; struct grub_reiserfs_data* data; TYPE_5__ header; } ;
typedef  int grub_uint64_t ;
typedef  char grub_uint32_t ;
typedef  scalar_t__ grub_uint16_t ;
typedef  scalar_t__ grub_ssize_t ;
typedef  scalar_t__ grub_size_t ;
typedef  scalar_t__ grub_off_t ;
typedef  TYPE_6__* grub_file_t ;
typedef  scalar_t__ grub_disk_addr_t ;
struct TYPE_15__ {int /*<<< orphan*/  read_hook; int /*<<< orphan*/  closure; } ;
struct TYPE_14__ {scalar_t__ offset; scalar_t__ size; int /*<<< orphan*/  read_hook; int /*<<< orphan*/  closure; struct grub_fshelp_node* data; } ;

/* Variables and functions */
 scalar_t__ GRUB_DISK_SECTOR_BITS ; 
 scalar_t__ GRUB_ERR_NONE ; 
 int /*<<< orphan*/  GRUB_REISERFS_ANY ; 
#define  GRUB_REISERFS_DIRECT 129 
#define  GRUB_REISERFS_INDIRECT 128 
 scalar_t__ MAX (int,int /*<<< orphan*/ ) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  grub_disk_read (TYPE_8__*,scalar_t__,scalar_t__,scalar_t__,char*) ; 
 int /*<<< orphan*/  grub_dprintf (char*,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_free (char*) ; 
 scalar_t__ grub_le_to_cpu16 (int /*<<< orphan*/ ) ; 
 scalar_t__ grub_le_to_cpu32 (char) ; 
 char* grub_malloc (scalar_t__) ; 
 scalar_t__ grub_reiserfs_get_item (struct grub_reiserfs_data*,struct grub_reiserfs_key*,struct grub_fshelp_node*) ; 
 int /*<<< orphan*/  grub_reiserfs_set_key_offset (struct grub_reiserfs_key*,int) ; 
 int /*<<< orphan*/  grub_reiserfs_set_key_type (struct grub_reiserfs_key*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static grub_ssize_t
grub_reiserfs_read (grub_file_t file, char *buf, grub_size_t len)
{
  unsigned int indirect_block, indirect_block_count;
  struct grub_reiserfs_key key;
  struct grub_fshelp_node *node = file->data;
  struct grub_reiserfs_data *data = node->data;
  struct grub_fshelp_node found;
  grub_uint16_t block_size = grub_le_to_cpu16 (data->superblock.block_size);
  grub_uint16_t item_size;
  grub_uint32_t *indirect_block_ptr = 0;
  grub_uint64_t current_key_offset = 1;
  grub_off_t initial_position, current_position, final_position, length;
  grub_disk_addr_t block;
  grub_off_t offset;

  key.directory_id = node->header.key.directory_id;
  key.object_id = node->header.key.object_id;
  key.u.v2.offset_type = 0;
  grub_reiserfs_set_key_type (&key, GRUB_REISERFS_ANY, 2);
  initial_position = file->offset;
  current_position = 0;
  final_position = MIN (len + initial_position, file->size);
  grub_dprintf ("reiserfs",
		"Reading from %lld to %lld (%lld instead of requested %ld)\n",
		(unsigned long long) initial_position,
		(unsigned long long) final_position,
		(unsigned long long) (final_position - initial_position),
		(unsigned long) len);
  while (current_position < final_position)
    {
      grub_reiserfs_set_key_offset (&key, current_key_offset);

      if (grub_reiserfs_get_item (data, &key, &found) != GRUB_ERR_NONE)
        goto fail;
      if (found.block_number == 0)
        goto fail;
      item_size = grub_le_to_cpu16 (found.header.item_size);
      switch (found.type)
        {
        case GRUB_REISERFS_DIRECT:
          block = (grub_disk_addr_t)found.block_number \
				  * ((grub_disk_addr_t)block_size  >> GRUB_DISK_SECTOR_BITS);
          grub_dprintf ("reiserfs_blocktype", "D: %u\n", (unsigned) block);
          if (initial_position < current_position + item_size)
            {
              offset = MAX ((signed) (initial_position - current_position), 0);
              length = (MIN (item_size, final_position - current_position)
                        - offset);
              grub_dprintf ("reiserfs",
                            "Reading direct block %u from %u to %u...\n",
                            (unsigned) block, (unsigned) offset,
                            (unsigned) (offset + length));
              found.data->disk->read_hook = file->read_hook;
	      found.data->disk->closure = file->closure;
              grub_disk_read (found.data->disk,
                              block,
                              offset
                              + grub_le_to_cpu16 (found.header.item_location),
                              length, buf);
              found.data->disk->read_hook = 0;
              if (grub_errno)
                goto fail;
              buf += length;
              current_position += offset + length;
            }
          else
            current_position += item_size;
          break;
        case GRUB_REISERFS_INDIRECT:
          indirect_block_count = item_size / sizeof (*indirect_block_ptr);
          indirect_block_ptr = grub_malloc (item_size);
          if (! indirect_block_ptr)
            goto fail;
          grub_disk_read (found.data->disk,
                          found.block_number * (block_size >> GRUB_DISK_SECTOR_BITS),
                          grub_le_to_cpu16 (found.header.item_location),
                          item_size, indirect_block_ptr);
          if (grub_errno)
            goto fail;
          found.data->disk->read_hook = file->read_hook;
          for (indirect_block = 0;
               indirect_block < indirect_block_count
                 && current_position < final_position;
               indirect_block++)
            {
              block = grub_le_to_cpu32 (indirect_block_ptr[indirect_block]) *
                      (block_size >> GRUB_DISK_SECTOR_BITS);
              grub_dprintf ("reiserfs_blocktype", "I: %u\n", (unsigned) block);
              if (current_position + block_size >= initial_position)
                {
                  offset = MAX ((signed) (initial_position - current_position),
                                0);
                  length = (MIN (block_size, final_position - current_position)
                            - offset);
                  grub_dprintf ("reiserfs",
                                "Reading indirect block %u from %u to %u...\n",
                                (unsigned) block, (unsigned) offset,
                                (unsigned) (offset + length));
#if 0
                  grub_dprintf ("reiserfs",
                                "\nib=%04d/%04d, ip=%d, cp=%d, fp=%d, off=%d, l=%d, tl=%d\n",
                                indirect_block + 1, indirect_block_count,
                                initial_position, current_position,
                                final_position, offset, length, len);
#endif
                  grub_disk_read (found.data->disk, block, offset, length, buf);
                  if (grub_errno)
                    goto fail;
                  buf += length;
                  current_position += offset + length;
                }
              else
                current_position += block_size;
            }
          found.data->disk->read_hook = 0;
          grub_free (indirect_block_ptr);
          indirect_block_ptr = 0;
          break;
        default:
          goto fail;
        }
      current_key_offset = current_position + 1;
    }

  grub_dprintf ("reiserfs",
		"Have successfully read %lld bytes (%ld requested)\n",
		(unsigned long long) (current_position - initial_position),
		(unsigned long) len);
  return current_position - initial_position;

#if 0
  switch (found.type)
    {
      case GRUB_REISERFS_DIRECT:
        read_length = MIN (len, item_size - file->offset);
        grub_disk_read (found.data->disk,
                        (found.block_number * block_size) / GRUB_DISK_SECTOR_SIZE,
                        grub_le_to_cpu16 (found.header.item_location) + file->offset,
                        read_length, buf);
        if (grub_errno)
          goto fail;
        break;
      case GRUB_REISERFS_INDIRECT:
        indirect_block_count = item_size / sizeof (*indirect_block_ptr);
        indirect_block_ptr = grub_malloc (item_size);
        if (!indirect_block_ptr)
          goto fail;
        grub_disk_read (found.data->disk,
                        (found.block_number * block_size) / GRUB_DISK_SECTOR_SIZE,
                        grub_le_to_cpu16 (found.header.item_location),
                        item_size, (char *) indirect_block_ptr);
        if (grub_errno)
          goto fail;
        len = MIN (len, file->size - file->offset);
        for (indirect_block = file->offset / block_size;
             indirect_block < indirect_block_count && read_length < len;
             indirect_block++)
          {
            read = MIN (block_size, len - read_length);
            grub_disk_read (found.data->disk,
                            (grub_le_to_cpu32 (indirect_block_ptr[indirect_block]) * block_size) / GRUB_DISK_SECTOR_SIZE,
                            file->offset % block_size, read,
                            ((void *) buf) + read_length);
            if (grub_errno)
              goto fail;
            read_length += read;
          }
        grub_free (indirect_block_ptr);
        break;
      default:
        goto fail;
    }

  return read_length;
#endif

 fail:
  grub_free (indirect_block_ptr);
  return 0;
}