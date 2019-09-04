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
struct TYPE_2__ {int /*<<< orphan*/  i_size; } ;
struct grub_fshelp_node {TYPE_1__ inode; int /*<<< orphan*/  ino; int /*<<< orphan*/  data; int /*<<< orphan*/  inode_read; } ;
typedef  struct grub_fshelp_node* grub_fshelp_node_t ;

/* Variables and functions */
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  grub_free (char*) ; 
 size_t grub_le_to_cpu64 (int /*<<< orphan*/ ) ; 
 char* grub_malloc (int) ; 
 int /*<<< orphan*/  grub_nilfs2_read_file (struct grub_fshelp_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,char*) ; 
 int /*<<< orphan*/  grub_nilfs2_read_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static char *
grub_nilfs2_read_symlink (grub_fshelp_node_t node)
{
  char *symlink;
  struct grub_fshelp_node *diro = node;

  if (!diro->inode_read)
    {
      grub_nilfs2_read_inode (diro->data, diro->ino, &diro->inode);
      if (grub_errno)
	return 0;
    }

  symlink = grub_malloc (grub_le_to_cpu64 (diro->inode.i_size) + 1);
  if (!symlink)
    return 0;

  grub_nilfs2_read_file (diro, 0, 0, 0, 0,
			 grub_le_to_cpu64 (diro->inode.i_size), symlink);
  if (grub_errno)
    {
      grub_free (symlink);
      return 0;
    }

  symlink[grub_le_to_cpu64 (diro->inode.i_size)] = '\0';
  return symlink;
}