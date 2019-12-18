#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; scalar_t__ attr_end; } ;
struct grub_ntfs_file {int inode_read; TYPE_2__ attr; int /*<<< orphan*/  size; int /*<<< orphan*/ * buf; int /*<<< orphan*/  sector; TYPE_1__* data; } ;
typedef  int /*<<< orphan*/  grub_uint32_t ;
typedef  int /*<<< orphan*/  grub_err_t ;
struct TYPE_4__ {int mft_size; } ;

/* Variables and functions */
 int AF_ALST ; 
 int /*<<< orphan*/  AT_DATA ; 
 int BLK_SHR ; 
 int /*<<< orphan*/  GRUB_ERR_BAD_FS ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * grub_malloc (int) ; 
 int /*<<< orphan*/  init_attr (TYPE_2__*,struct grub_ntfs_file*) ; 
 char* locate_attr (TYPE_2__*,struct grub_ntfs_file*,int /*<<< orphan*/ ) ; 
 scalar_t__ read_mft (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned short u16at (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  u32at (char*,int) ; 
 int /*<<< orphan*/  u64at (char*,int) ; 

__attribute__((used)) static grub_err_t
init_file (struct grub_ntfs_file *mft, grub_uint32_t mftno)
{
  unsigned short flag;

  mft->inode_read = 1;

  mft->buf = grub_malloc (mft->data->mft_size << BLK_SHR);
  if (mft->buf == NULL)
    return grub_errno;

  if (read_mft (mft->data, mft->buf, mftno, &mft->sector))
    return grub_errno;

  flag = u16at (mft->buf, 0x16);
  if ((flag & 1) == 0)
    return grub_error (GRUB_ERR_BAD_FS, "MFT 0x%X is not in use", mftno);

  if ((flag & 2) == 0)
    {
      char *pa;

      pa = locate_attr (&mft->attr, mft, AT_DATA);
      if (pa == NULL)
	return grub_error (GRUB_ERR_BAD_FS, "no $DATA in MFT 0x%X", mftno);

      if (!pa[8])
	mft->size = u32at (pa, 0x10);
      else
	mft->size = u64at (pa, 0x30);

      if ((mft->attr.flags & AF_ALST) == 0)
	mft->attr.attr_end = 0;	/*  Don't jump to attribute list */
    }
  else
    init_attr (&mft->attr, mft);

  return 0;
}