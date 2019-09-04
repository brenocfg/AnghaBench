#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int grub_ssize_t ;
typedef  TYPE_3__* grub_fshelp_node_t ;
struct TYPE_6__ {int /*<<< orphan*/  raw; } ;
struct TYPE_7__ {int format; TYPE_1__ data; int /*<<< orphan*/  size; } ;
struct TYPE_8__ {TYPE_2__ inode; } ;

/* Variables and functions */
#define  XFS_INODE_FORMAT_EXT 129 
#define  XFS_INODE_FORMAT_INO 128 
 int grub_be_to_cpu64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_free (char*) ; 
 char* grub_malloc (int) ; 
 char* grub_strndup (int /*<<< orphan*/ ,int) ; 
 int grub_xfs_read_file (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static char *
grub_xfs_read_symlink (grub_fshelp_node_t node)
{
  int size = grub_be_to_cpu64 (node->inode.size);

  switch (node->inode.format)
    {
    case XFS_INODE_FORMAT_INO:
      return grub_strndup (node->inode.data.raw, size);

    case XFS_INODE_FORMAT_EXT:
      {
	char *symlink;
	grub_ssize_t numread;

	symlink = grub_malloc (size + 1);
	if (!symlink)
	  return 0;

	numread = grub_xfs_read_file (node, 0, 0, 0, 0, size, symlink);
	if (numread != size)
	  {
	    grub_free (symlink);
	    return 0;
	  }
	symlink[size] = '\0';
	return symlink;
      }
    }

  return 0;
}