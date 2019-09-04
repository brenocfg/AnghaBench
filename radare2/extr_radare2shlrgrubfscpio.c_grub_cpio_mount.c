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
struct head {scalar_t__ magic; } ;
struct grub_cpio_data {int /*<<< orphan*/  disk; } ;
typedef  int /*<<< orphan*/  hd ;
typedef  int /*<<< orphan*/  grub_disk_t ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_FS ; 
 scalar_t__ MAGIC_BCPIO ; 
 int /*<<< orphan*/  grub_cpio_convert_header (struct head*) ; 
 scalar_t__ grub_disk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct head*) ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ grub_malloc (int) ; 

__attribute__((used)) static struct grub_cpio_data *
grub_cpio_mount (grub_disk_t disk)
{
  struct head hd;
  struct grub_cpio_data *data;
  int test;

  if (grub_disk_read (disk, 0, 0, sizeof (hd), &hd))
    goto fail;

#ifndef MODE_USTAR
  grub_cpio_convert_header (&hd);
  test = hd.magic != MAGIC_BCPIO;
#else
  test = grub_memcmp (hd.magic, MAGIC_USTAR,
		   sizeof (MAGIC_USTAR) - 1);
#endif
    if (test)
    	goto fail;

  data = (struct grub_cpio_data *) grub_malloc (sizeof (*data));
  if (!data)
    goto fail;

  data->disk = disk;

  return data;

fail:
  grub_error (GRUB_ERR_BAD_FS, "not a "
#ifdef MODE_USTAR
	      "tar"
#else
	      "cpio"
#endif
	      " filesystem");
  return 0;
}