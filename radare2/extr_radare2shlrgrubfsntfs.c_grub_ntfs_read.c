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
struct TYPE_5__ {int save_pos; } ;
struct grub_ntfs_file {TYPE_2__ attr; } ;
struct grub_ntfs_data {struct grub_ntfs_file cmft; } ;
typedef  int /*<<< orphan*/  grub_ssize_t ;
typedef  int /*<<< orphan*/  grub_size_t ;
typedef  TYPE_1__* grub_file_t ;
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  closure; int /*<<< orphan*/  read_hook; int /*<<< orphan*/  offset; scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  read_attr (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static grub_ssize_t
grub_ntfs_read (grub_file_t file, char *buf, grub_size_t len)
{
  struct grub_ntfs_file *mft;

  mft = &((struct grub_ntfs_data *) file->data)->cmft;
  if (file->read_hook)
    mft->attr.save_pos = 1;

  read_attr (&mft->attr, buf, file->offset, len, 1,
	     file->read_hook, file->closure, file->flags);
  return (grub_errno) ? 0 : len;
}