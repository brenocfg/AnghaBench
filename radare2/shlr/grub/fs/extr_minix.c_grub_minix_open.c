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
struct grub_minix_data {int dummy; } ;
struct grub_file {int /*<<< orphan*/  size; struct grub_minix_data* data; TYPE_1__* device; } ;
typedef  scalar_t__ grub_err_t ;
struct TYPE_2__ {int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_FILENAME ; 
 scalar_t__ GRUB_ERR_NONE ; 
 int /*<<< orphan*/  GRUB_MINIX_INODE_SIZE (struct grub_minix_data*) ; 
 int /*<<< orphan*/  GRUB_MINIX_ROOT_INODE ; 
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  grub_free (struct grub_minix_data*) ; 
 int /*<<< orphan*/  grub_minix_find_file (struct grub_minix_data*,char const*) ; 
 struct grub_minix_data* grub_minix_mount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_minix_read_inode (struct grub_minix_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static grub_err_t
grub_minix_open (struct grub_file *file, const char *name)
{
  struct grub_minix_data *data;
  data = grub_minix_mount (file->device->disk);
  if (!data)
    return grub_errno;

  /* Open the inode op the root directory.  */
  grub_minix_read_inode (data, GRUB_MINIX_ROOT_INODE);
  if (grub_errno)
    {
      grub_free (data);
      return grub_errno;
    }

  if (!name || name[0] != '/')
    {
      grub_error (GRUB_ERR_BAD_FILENAME, "bad filename");
      return grub_errno;
    }

  /* Traverse the directory tree to the node that should be
     opened.  */
  grub_minix_find_file (data, name);
  if (grub_errno)
    {
      grub_free (data);
      return grub_errno;
    }

  file->data = data;
  file->size = GRUB_MINIX_INODE_SIZE (data);

  return GRUB_ERR_NONE;
}