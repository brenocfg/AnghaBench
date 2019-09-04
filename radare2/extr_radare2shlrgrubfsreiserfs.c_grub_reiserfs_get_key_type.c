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
struct grub_reiserfs_key {int dummy; } ;
typedef  enum grub_reiserfs_item_type { ____Placeholder_grub_reiserfs_item_type } grub_reiserfs_item_type ;

/* Variables and functions */
 int grub_reiserfs_get_key_v1_type (struct grub_reiserfs_key const*) ; 
 int grub_reiserfs_get_key_v2_type (struct grub_reiserfs_key const*) ; 
 int grub_reiserfs_get_key_version (struct grub_reiserfs_key const*) ; 

__attribute__((used)) static enum grub_reiserfs_item_type
grub_reiserfs_get_key_type (const struct grub_reiserfs_key *key)
{
  if (grub_reiserfs_get_key_version (key) == 1)
    return grub_reiserfs_get_key_v1_type (key);
  else
    return grub_reiserfs_get_key_v2_type (key);
}