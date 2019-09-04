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
struct TYPE_5__ {int /*<<< orphan*/  offset_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;
struct TYPE_6__ {TYPE_2__ v2; TYPE_1__ v1; } ;
struct grub_reiserfs_key {TYPE_3__ u; } ;
typedef  unsigned long long grub_uint64_t ;

/* Variables and functions */
 unsigned long long grub_le_to_cpu32 (int /*<<< orphan*/ ) ; 
 unsigned long long grub_le_to_cpu64 (int /*<<< orphan*/ ) ; 
 int grub_reiserfs_get_key_version (struct grub_reiserfs_key const*) ; 

__attribute__((used)) static grub_uint64_t
grub_reiserfs_get_key_offset (const struct grub_reiserfs_key *key)
{
  if (grub_reiserfs_get_key_version (key) == 1)
    return grub_le_to_cpu32 (key->u.v1.offset);
  else
    return grub_le_to_cpu64 (key->u.v2.offset_type) & (~0ULL >> 4);
}