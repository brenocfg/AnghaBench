#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  attr; } ;
struct grub_ntfs_data {int mft_size; TYPE_1__ mmft; } ;
typedef  int grub_uint32_t ;
typedef  int /*<<< orphan*/  grub_err_t ;
typedef  int grub_disk_addr_t ;

/* Variables and functions */
 int BLK_SHR ; 
 int /*<<< orphan*/  GRUB_ERR_BAD_FS ; 
 int /*<<< orphan*/  fixup (struct grub_ntfs_data*,char*,int,char*) ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ read_attr (int /*<<< orphan*/ *,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_mft_hook ; 

__attribute__((used)) static grub_err_t
read_mft (struct grub_ntfs_data *data, char *buf, grub_uint32_t mftno,
	  grub_uint32_t *sector)
{
  if (read_attr
      (&data->mmft.attr, buf, mftno * ((grub_disk_addr_t) data->mft_size << BLK_SHR),
       data->mft_size << BLK_SHR, 0, read_mft_hook, &sector, 0))
    return grub_error (GRUB_ERR_BAD_FS, "Read MFT 0x%X fails", mftno);
  return fixup (data, buf, data->mft_size, "FILE");
}