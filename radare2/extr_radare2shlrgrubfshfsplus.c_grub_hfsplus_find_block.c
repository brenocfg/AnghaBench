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
struct grub_hfsplus_extent {int /*<<< orphan*/  count; int /*<<< orphan*/  start; } ;
typedef  int grub_size_t ;

/* Variables and functions */
 int grub_be_to_cpu32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
grub_hfsplus_find_block (struct grub_hfsplus_extent *extent,
			 int *fileblock)
{
  int i;
  grub_size_t blksleft = *fileblock;

  /* First lookup the file in the given extents.  */
  for (i = 0; i < 8; i++)
    {
      if (blksleft < grub_be_to_cpu32 (extent[i].count))
	return grub_be_to_cpu32 (extent[i].start) + blksleft;
      blksleft -= grub_be_to_cpu32 (extent[i].count);
    }

  *fileblock = blksleft;
  return -1;
}