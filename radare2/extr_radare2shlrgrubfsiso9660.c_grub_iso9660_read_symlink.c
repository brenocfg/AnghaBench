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
struct grub_iso9660_read_symlink_closure {char* symlink; scalar_t__ addslash; } ;
struct grub_iso9660_dir {int namelen; int len; } ;
typedef  TYPE_1__* grub_fshelp_node_t ;
typedef  int /*<<< orphan*/  dirent ;
struct TYPE_5__ {int susp_skip; int /*<<< orphan*/  disk; } ;
struct TYPE_4__ {scalar_t__ dir_off; int /*<<< orphan*/  dir_blk; TYPE_2__* data; } ;

/* Variables and functions */
 scalar_t__ grub_disk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,char*) ; 
 int /*<<< orphan*/  grub_free (char*) ; 
 scalar_t__ grub_iso9660_susp_iterate (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,struct grub_iso9660_read_symlink_closure*) ; 
 char* grub_malloc (int) ; 
 int /*<<< orphan*/  susp_iterate_sl ; 

__attribute__((used)) static char *
grub_iso9660_read_symlink (grub_fshelp_node_t node)
{
  struct grub_iso9660_dir dirent;
  int sua_off;
  int sua_size;
  struct grub_iso9660_read_symlink_closure c;

  if (grub_disk_read (node->data->disk, node->dir_blk, node->dir_off,
		      sizeof (dirent), (char *) &dirent))
    return 0;

  sua_off = (sizeof (dirent) + dirent.namelen + 1 - (dirent.namelen % 2)
	     + node->data->susp_skip);
  sua_size = dirent.len - sua_off;

  c.symlink = grub_malloc (1);
  if (!c.symlink)
    return 0;

  *c.symlink = '\0';

  c.addslash = 0;
  if (grub_iso9660_susp_iterate (node->data, node->dir_blk,
				 node->dir_off + sua_off,
				 sua_size, susp_iterate_sl, &c))
    {
      grub_free (c.symlink);
      return 0;
    }

  return c.symlink;
}