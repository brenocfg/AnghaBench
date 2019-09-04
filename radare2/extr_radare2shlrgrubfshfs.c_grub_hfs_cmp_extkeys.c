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
struct grub_hfs_extent_key {int forktype; int /*<<< orphan*/  first_block; int /*<<< orphan*/  fileid; } ;

/* Variables and functions */
 int grub_be_to_cpu16 (int /*<<< orphan*/ ) ; 
 int grub_be_to_cpu32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
grub_hfs_cmp_extkeys (struct grub_hfs_extent_key *k1,
		      struct grub_hfs_extent_key *k2)
{
  int cmp = k1->forktype - k2->forktype;
  if (cmp == 0)
    cmp = grub_be_to_cpu32 (k1->fileid) - grub_be_to_cpu32 (k2->fileid);
  if (cmp == 0)
    cmp = (grub_be_to_cpu16 (k1->first_block)
	   - grub_be_to_cpu16 (k2->first_block));
  return cmp;
}