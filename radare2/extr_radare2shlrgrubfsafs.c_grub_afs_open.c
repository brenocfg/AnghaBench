#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct grub_fshelp_node {TYPE_3__* inode; int /*<<< orphan*/  diropen; } ;
struct grub_file {scalar_t__ offset; struct grub_fshelp_node* data; int /*<<< orphan*/  size; TYPE_1__* device; } ;
struct grub_afs_inode {int dummy; } ;
struct grub_afs_data {TYPE_3__* inode; int /*<<< orphan*/  diropen; } ;
typedef  scalar_t__ grub_err_t ;
struct TYPE_6__ {int /*<<< orphan*/  size; } ;
struct TYPE_7__ {TYPE_2__ stream; } ;
struct TYPE_5__ {int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_FSHELP_REG ; 
 int /*<<< orphan*/  grub_afs_iterate_dir ; 
 struct grub_fshelp_node* grub_afs_mount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_afs_read_symlink ; 
 int /*<<< orphan*/  grub_afs_to_cpu64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_dl_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_dl_unref (int /*<<< orphan*/ ) ; 
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  grub_free (struct grub_fshelp_node*) ; 
 int /*<<< orphan*/  grub_fshelp_find_file (char const*,int /*<<< orphan*/ *,struct grub_fshelp_node**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_memcpy (TYPE_3__*,TYPE_3__**,int) ; 
 int /*<<< orphan*/  my_mod ; 

__attribute__((used)) static grub_err_t
grub_afs_open (struct grub_file *file, const char *name)
{
  struct grub_afs_data *data;
  struct grub_fshelp_node *fdiro = 0;

  grub_dl_ref (my_mod);

  data = grub_afs_mount (file->device->disk);
  if (! data)
    goto fail;

  grub_fshelp_find_file (name, &data->diropen, &fdiro, grub_afs_iterate_dir, 0,
			 grub_afs_read_symlink, GRUB_FSHELP_REG);
  if (grub_errno)
    goto fail;

  grub_memcpy (data->inode, &fdiro->inode, sizeof (struct grub_afs_inode));
  grub_free (fdiro);

  file->size = grub_afs_to_cpu64 (data->inode->stream.size);
  file->data = data;
  file->offset = 0;

  return 0;

fail:
  grub_free (data);

  grub_dl_unref (my_mod);

  return grub_errno;
}