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
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;
struct TYPE_6__ {TYPE_2__ v2; TYPE_1__ v1; } ;
struct grub_reiserfs_key {TYPE_3__ u; } ;
typedef  unsigned long long grub_uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  grub_cpu_to_le32 (unsigned long long) ; 
 int grub_cpu_to_le64 (unsigned long long) ; 
 int grub_reiserfs_get_key_version (struct grub_reiserfs_key*) ; 

__attribute__((used)) static void
grub_reiserfs_set_key_offset (struct grub_reiserfs_key *key,
                              grub_uint64_t value)
{
  if (grub_reiserfs_get_key_version (key) == 1)
    key->u.v1.offset = grub_cpu_to_le32 (value);
  else
    key->u.v2.offset_type \
      = ((key->u.v2.offset_type & grub_cpu_to_le64 (15ULL << 60))
         | grub_cpu_to_le64 (value & (~0ULL >> 4)));
}