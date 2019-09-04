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
struct grub_reiserfs_key {int /*<<< orphan*/  object_id; int /*<<< orphan*/  directory_id; } ;
typedef  scalar_t__ grub_uint64_t ;
typedef  scalar_t__ grub_uint32_t ;
typedef  enum grub_reiserfs_item_type { ____Placeholder_grub_reiserfs_item_type } grub_reiserfs_item_type ;

/* Variables and functions */
 int GRUB_REISERFS_ANY ; 
 int GRUB_REISERFS_DIRECT ; 
 int GRUB_REISERFS_INDIRECT ; 
 scalar_t__ grub_le_to_cpu32 (int /*<<< orphan*/ ) ; 
 scalar_t__ grub_reiserfs_get_key_offset (struct grub_reiserfs_key const*) ; 
 int grub_reiserfs_get_key_type (struct grub_reiserfs_key const*) ; 

__attribute__((used)) static int
grub_reiserfs_compare_keys (const struct grub_reiserfs_key *key1,
                            const struct grub_reiserfs_key *key2)
{
  grub_uint64_t offset1, offset2;
  enum grub_reiserfs_item_type type1, type2;
  grub_uint32_t id1, id2;

  if (! key1 || ! key2)
    return -2;

  id1 = grub_le_to_cpu32 (key1->directory_id);
  id2 = grub_le_to_cpu32 (key2->directory_id);
  if (id1 < id2)
    return -1;
  if (id1 > id2)
    return 1;

  id1 = grub_le_to_cpu32 (key1->object_id);
  id2 = grub_le_to_cpu32 (key2->object_id);
  if (id1 < id2)
    return -1;
  if (id1 > id2)
    return 1;

  offset1 = grub_reiserfs_get_key_offset (key1);
  offset2 = grub_reiserfs_get_key_offset (key2);
  if (offset1 < offset2)
    return -1;
  if (offset1 > offset2)
    return 1;

  type1 = grub_reiserfs_get_key_type (key1);
  type2 = grub_reiserfs_get_key_type (key2);
  if ((type1 == GRUB_REISERFS_ANY
       && (type2 == GRUB_REISERFS_DIRECT
           || type2 == GRUB_REISERFS_INDIRECT))
      || (type2 == GRUB_REISERFS_ANY
          && (type1 == GRUB_REISERFS_DIRECT
              || type1 == GRUB_REISERFS_INDIRECT)))
    return 0;
  if (type1 < type2)
    return -1;
  if (type1 > type2)
    return 1;

  return 0;
}