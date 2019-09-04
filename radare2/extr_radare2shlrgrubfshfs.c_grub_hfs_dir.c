#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct grub_hfs_filerec {scalar_t__ type; int /*<<< orphan*/  member_0; } ;
struct grub_hfs_dir_closure {int (* hook ) (char const*,struct grub_dirhook_info const*,void*) ;void* closure; } ;
struct grub_hfs_data {int /*<<< orphan*/  cat_root; } ;
typedef  int /*<<< orphan*/  grub_err_t ;
typedef  TYPE_1__* grub_device_t ;
struct TYPE_3__ {int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_FILE_TYPE ; 
 scalar_t__ GRUB_HFS_FILETYPE_DIR ; 
 int /*<<< orphan*/  grub_dl_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_dl_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  grub_free (struct grub_hfs_data*) ; 
 int /*<<< orphan*/  grub_hfs_dir_hook ; 
 scalar_t__ grub_hfs_find_dir (struct grub_hfs_data*,char const*,struct grub_hfs_filerec*,int*) ; 
 int /*<<< orphan*/  grub_hfs_iterate_dir (struct grub_hfs_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct grub_hfs_dir_closure*) ; 
 struct grub_hfs_data* grub_hfs_mount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_mod ; 

__attribute__((used)) static grub_err_t
grub_hfs_dir (grub_device_t device, const char *path,
	      int (*hook) (const char *filename,
			   const struct grub_dirhook_info *info, void *closure),
	      void *closure)
{
  int inode;
  struct grub_hfs_data *data;
  struct grub_hfs_filerec frec = {0};
  struct grub_hfs_dir_closure c;

  grub_dl_ref (my_mod);

  data = grub_hfs_mount (device->disk);
  if (!data)
    goto fail;

  /* First the directory ID for the directory.  */
  if (grub_hfs_find_dir (data, path, &frec, &inode))
    goto fail;

  if (frec.type != GRUB_HFS_FILETYPE_DIR)
    {
      grub_error (GRUB_ERR_BAD_FILE_TYPE, "not a directory");
      goto fail;
    }

  c.hook = hook;
  c.closure = closure;
  grub_hfs_iterate_dir (data, data->cat_root, inode, grub_hfs_dir_hook, &c);

 fail:
  grub_free (data);

  grub_dl_unref (my_mod);

  return grub_errno;
}