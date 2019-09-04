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
typedef  int /*<<< orphan*/  grub_uint32_t ;
typedef  int /*<<< orphan*/  grub_disk_addr_t ;

/* Variables and functions */
 unsigned int GRUB_DISK_SECTOR_SIZE ; 
 int /*<<< orphan*/  GRUB_ERR_BAD_FS ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
read_mft_hook (grub_disk_addr_t sector, unsigned offset,
	       unsigned length, void *closure)
{
  grub_uint32_t **s = closure;

  if (*s)
    {
      if ((offset != 0) || (length != GRUB_DISK_SECTOR_SIZE))
	grub_error (GRUB_ERR_BAD_FS, "invalid mft location");
      **s = sector;
      *s = 0;
    }
}