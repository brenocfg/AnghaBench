#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct grub_ext2_dir_closure {int (* hook ) (char const*,struct grub_dirhook_info*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  closure; int /*<<< orphan*/  data; } ;
struct grub_dirhook_info {int mtimeset; int dir; int /*<<< orphan*/  mtime; } ;
typedef  int /*<<< orphan*/  info ;
typedef  TYPE_1__* grub_fshelp_node_t ;
typedef  enum grub_fshelp_filetype { ____Placeholder_grub_fshelp_filetype } grub_fshelp_filetype ;
struct TYPE_6__ {int /*<<< orphan*/  mtime; } ;
struct TYPE_5__ {int inode_read; TYPE_4__ inode; int /*<<< orphan*/  ino; } ;

/* Variables and functions */
 scalar_t__ GRUB_ERR_NONE ; 
 int GRUB_FSHELP_DIR ; 
 int GRUB_FSHELP_TYPE_MASK ; 
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  grub_ext2_read_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  grub_free (TYPE_1__*) ; 
 int /*<<< orphan*/  grub_le_to_cpu32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_memset (struct grub_dirhook_info*,int /*<<< orphan*/ ,int) ; 
 int stub1 (char const*,struct grub_dirhook_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iterate (const char *filename,
	 enum grub_fshelp_filetype filetype,
	 grub_fshelp_node_t node,
	 void *closure)
{
  struct grub_ext2_dir_closure *c = closure;
  struct grub_dirhook_info info;
  grub_memset (&info, 0, sizeof (info));
  if (! node->inode_read)
    {
      grub_ext2_read_inode (c->data, node->ino, &node->inode);
      if (!grub_errno)
	node->inode_read = 1;
      grub_errno = GRUB_ERR_NONE;
    }
  if (node->inode_read)
    {
      info.mtimeset = 1;
      info.mtime = grub_le_to_cpu32 (node->inode.mtime);
    }

  info.dir = ((filetype & GRUB_FSHELP_TYPE_MASK) == GRUB_FSHELP_DIR);
  grub_free (node);
  return (c->hook != NULL)? c->hook (filename, &info, c->closure): 0;
}