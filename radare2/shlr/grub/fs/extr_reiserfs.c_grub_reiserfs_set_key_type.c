#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int offset_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {TYPE_2__ v2; TYPE_1__ v1; } ;
struct grub_reiserfs_key {TYPE_3__ u; } ;
typedef  int grub_uint64_t ;
typedef  int grub_uint32_t ;
typedef  enum grub_reiserfs_item_type { ____Placeholder_grub_reiserfs_item_type } grub_reiserfs_item_type ;

/* Variables and functions */
#define  GRUB_REISERFS_ANY 132 
#define  GRUB_REISERFS_DIRECT 131 
#define  GRUB_REISERFS_DIRECTORY 130 
#define  GRUB_REISERFS_INDIRECT 129 
#define  GRUB_REISERFS_STAT 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  grub_cpu_to_le32 (int) ; 
 int grub_cpu_to_le64 (int) ; 
 int grub_reiserfs_get_key_type (struct grub_reiserfs_key*) ; 

__attribute__((used)) static void
grub_reiserfs_set_key_type (struct grub_reiserfs_key *key,
                            enum grub_reiserfs_item_type grub_type,
                            int version)
{
  grub_uint32_t type;

  switch (grub_type)
    {
    case GRUB_REISERFS_STAT:
      type = 0;
      break;
    case GRUB_REISERFS_ANY:
      type = (version == 1) ? 555 : 15;
      break;
    case GRUB_REISERFS_DIRECTORY:
      type = (version == 1) ? 500 : 3;
      break;
    case GRUB_REISERFS_DIRECT:
      type = (version == 1) ? 0xFFFFFFFF : 2;
      break;
    case GRUB_REISERFS_INDIRECT:
      type = (version == 1) ? 0xFFFFFFFE : 1;
      break;
    default:
      return;
    }

  if (version == 1)
    key->u.v1.type = grub_cpu_to_le32 (type);
  else
    key->u.v2.offset_type
      = ((key->u.v2.offset_type & grub_cpu_to_le64 (~0ULL >> 4))
         | grub_cpu_to_le64 ((grub_uint64_t) type << 60));

  assert (grub_reiserfs_get_key_type (key) == grub_type);
}