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
struct grub_minix_data {scalar_t__ linknest; } ;
typedef  scalar_t__ grub_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_SYMLINK_LOOP ; 
 size_t GRUB_MINIX_INODE_SIZE (struct grub_minix_data*) ; 
 scalar_t__ GRUB_MINIX_MAX_SYMLNK_CNT ; 
 int GRUB_MINIX_ROOT_INODE ; 
 scalar_t__ grub_errno ; 
 scalar_t__ grub_error (scalar_t__,char*,...) ; 
 char* grub_malloc (int) ; 
 int /*<<< orphan*/  grub_minix_find_file (struct grub_minix_data*,char*) ; 
 scalar_t__ grub_minix_read_file (struct grub_minix_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,char*) ; 
 scalar_t__ grub_minix_read_inode (struct grub_minix_data*,int) ; 

__attribute__((used)) static grub_err_t
grub_minix_lookup_symlink (struct grub_minix_data *data, int ino)
{
#ifndef _MSC_VER
  char symlink[GRUB_MINIX_INODE_SIZE (data) + 1];
#else
  char *symlink = grub_malloc(GRUB_MINIX_INODE_SIZE (data) + 1);
#endif
  if (++data->linknest > GRUB_MINIX_MAX_SYMLNK_CNT)
    return grub_error (GRUB_ERR_SYMLINK_LOOP, "too deep nesting of symlinks");

  if (grub_minix_read_file (data, 0, 0, 0,
			    GRUB_MINIX_INODE_SIZE (data), symlink) < 0)
    return grub_errno;

  symlink[GRUB_MINIX_INODE_SIZE (data)] = '\0';

  /* The symlink is an absolute path, go back to the root inode.  */
  if (symlink[0] == '/')
    ino = GRUB_MINIX_ROOT_INODE;

  /* Now load in the old inode.  */
  if (grub_minix_read_inode (data, ino))
    return grub_errno;

  grub_minix_find_file (data, symlink);
  if (grub_errno)
    grub_error (grub_errno, "cannot follow symlink `%s'", symlink);

  return grub_errno;
}