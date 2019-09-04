#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__ v1; } ;
struct grub_reiserfs_key {TYPE_2__ u; } ;
typedef  enum grub_reiserfs_item_type { ____Placeholder_grub_reiserfs_item_type } grub_reiserfs_item_type ;

/* Variables and functions */
 int GRUB_REISERFS_ANY ; 
 int GRUB_REISERFS_DIRECT ; 
 int GRUB_REISERFS_DIRECTORY ; 
 int GRUB_REISERFS_INDIRECT ; 
 int GRUB_REISERFS_STAT ; 
 int GRUB_REISERFS_UNKNOWN ; 
 int grub_le_to_cpu32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum grub_reiserfs_item_type
grub_reiserfs_get_key_v1_type (const struct grub_reiserfs_key *key)
{
  switch (grub_le_to_cpu32 (key->u.v1.type))
    {
    case 0:
      return GRUB_REISERFS_STAT;
    case 555:
      return GRUB_REISERFS_ANY;
    case 500:
      return GRUB_REISERFS_DIRECTORY;
    case 0x20000000:
    case 0xFFFFFFFF:
      return GRUB_REISERFS_DIRECT;
    case 0x10000000:
    case 0xFFFFFFFE:
      return GRUB_REISERFS_INDIRECT;
    }
  return GRUB_REISERFS_UNKNOWN;
}