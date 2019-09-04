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
struct grub_hfs_filerec {scalar_t__ type; } ;
struct grub_hfs_dirrec {int /*<<< orphan*/  dirid; } ;
struct grub_hfs_data {int rootdir; int /*<<< orphan*/  cat_root; } ;
struct grub_hfs_catalog_key {scalar_t__ str; scalar_t__ strlen; int /*<<< orphan*/  parent_dir; } ;
typedef  scalar_t__ grub_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_FILENAME ; 
 int /*<<< orphan*/  GRUB_ERR_BAD_FILE_TYPE ; 
 int /*<<< orphan*/  GRUB_ERR_FILE_NOT_FOUND ; 
 scalar_t__ GRUB_HFS_FILETYPE_DIR ; 
 int grub_be_to_cpu32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_cpu_to_be32 (int) ; 
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  grub_free (char*) ; 
 int /*<<< orphan*/  grub_hfs_find_node (struct grub_hfs_data*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  grub_memcpy (struct grub_hfs_filerec*,struct grub_hfs_filerec*,int) ; 
 char* grub_strchr (char const*,char) ; 
 int /*<<< orphan*/  grub_strcpy (char*,char const*) ; 
 char* grub_strdup (char const*) ; 
 scalar_t__ grub_strlen (char const*) ; 

__attribute__((used)) static grub_err_t
grub_hfs_find_dir (struct grub_hfs_data *data, const char *path,
		   struct grub_hfs_filerec *retdata, int *retinode)
{
  int inode = data->rootdir;
  char *next;
  char *origpath;
  union {
    struct grub_hfs_filerec frec;
    struct grub_hfs_dirrec dir;
  } fdrec;

  fdrec.frec.type = GRUB_HFS_FILETYPE_DIR;

  if (path[0] != '/')
    {
      grub_error (GRUB_ERR_BAD_FILENAME, "bad filename");
      return 0;
    }

  origpath = grub_strdup (path);
  if (!origpath)
    return grub_errno;

  path = origpath;
  while (*path == '/')
    path++;

  while (path && grub_strlen (path))
    {
      if (fdrec.frec.type != GRUB_HFS_FILETYPE_DIR)
	{
	  grub_error (GRUB_ERR_BAD_FILE_TYPE, "not a directory");
	  goto fail;
	}

      /* Isolate a part of the path.  */
      next = grub_strchr (path, '/');
      if (next)
	{
	  while (*next == '/')
	    *(next++) = '\0';
	}

      struct grub_hfs_catalog_key key;

      key.parent_dir = grub_cpu_to_be32 (inode);
      key.strlen = grub_strlen (path);
      grub_strcpy ((char *) (key.str), path);

      /* Lookup this node.  */
      if (! grub_hfs_find_node (data, (char *) &key, data->cat_root,
				0, (char *) &fdrec.frec, sizeof (fdrec.frec)))
	{
	  grub_error (GRUB_ERR_FILE_NOT_FOUND, "file not found");
	  goto fail;
	}

      if (grub_errno)
	goto fail;

      inode = grub_be_to_cpu32 (fdrec.dir.dirid);
      path = next;
    }

  if (retdata)
    grub_memcpy (retdata, &fdrec.frec, sizeof (fdrec.frec));

  if (retinode)
    *retinode = inode;

 fail:
  grub_free (origpath);
  return grub_errno;
}