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
struct grub_hfsplus_extkey_internal {int fileid; int start; } ;
struct grub_hfsplus_key_internal {struct grub_hfsplus_extkey_internal extkey; } ;
struct grub_hfsplus_extkey {int /*<<< orphan*/  start; int /*<<< orphan*/  fileid; } ;
struct grub_hfsplus_key {struct grub_hfsplus_extkey extkey; } ;

/* Variables and functions */
 int grub_be_to_cpu32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
grub_hfsplus_cmp_extkey (struct grub_hfsplus_key *keya,
			 struct grub_hfsplus_key_internal *keyb)
{
  struct grub_hfsplus_extkey *extkey_a = &keya->extkey;
  struct grub_hfsplus_extkey_internal *extkey_b = &keyb->extkey;
  int diff;

  diff = grub_be_to_cpu32 (extkey_a->fileid) - extkey_b->fileid;

  if (diff)
    return diff;

  diff = grub_be_to_cpu32 (extkey_a->start) - extkey_b->start;
  return diff;
}