#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct grub_affs_iterate_dir_closure {int (* hook ) (char const*,int,TYPE_1__*,void*) ;int /*<<< orphan*/ * node; int /*<<< orphan*/ * hashtable; struct grub_affs_file* file; struct grub_affs_data* data; void* closure; } ;
struct grub_affs_file {char* name; size_t namelen; int /*<<< orphan*/  next; int /*<<< orphan*/  size; int /*<<< orphan*/  type; } ;
struct grub_affs_data {int htsize; int blocksize; int /*<<< orphan*/  disk; } ;
typedef  scalar_t__ grub_uint64_t ;
typedef  int /*<<< orphan*/  grub_uint32_t ;
typedef  TYPE_1__* grub_fshelp_node_t ;
typedef  int /*<<< orphan*/  file ;
typedef  enum grub_fshelp_filetype { ____Placeholder_grub_fshelp_filetype } grub_fshelp_filetype ;
struct TYPE_5__ {scalar_t__ size; scalar_t__ block; scalar_t__ parent; struct grub_affs_data* data; } ;

/* Variables and functions */
 int GRUB_AFFS_FILETYPE_DIR ; 
 scalar_t__ GRUB_AFFS_FILETYPE_REG ; 
 scalar_t__ GRUB_AFFS_FILETYPE_SYMLINK ; 
 scalar_t__ GRUB_AFFS_FILE_LOCATION ; 
 scalar_t__ GRUB_AFFS_HASHTABLE_OFFSET ; 
 int GRUB_DISK_SECTOR_SIZE ; 
 int GRUB_FSHELP_DIR ; 
 int GRUB_FSHELP_REG ; 
 int GRUB_FSHELP_SYMLINK ; 
 int GRUB_FSHELP_UNKNOWN ; 
 scalar_t__ grub_affs_create_node (char*,scalar_t__,scalar_t__,int,struct grub_affs_iterate_dir_closure*) ; 
 scalar_t__ grub_be_to_cpu32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_disk_read (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,char*) ; 
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  grub_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * grub_malloc (int) ; 

__attribute__((used)) static int
grub_affs_iterate_dir (grub_fshelp_node_t dir,
		       int (*hook) (const char *filename,
				    enum grub_fshelp_filetype filetype,
				    grub_fshelp_node_t node, void *closure),
		       void *closure)
{
  int i;
  struct grub_affs_file file;
  struct grub_affs_data *data = dir->data;
  grub_uint32_t *hashtable;
  struct grub_affs_iterate_dir_closure c;

  c.hook = hook;
  c.closure = closure;
  c.node = 0;
  c.data = data;
  c.file = &file;

  hashtable = grub_malloc (data->htsize * sizeof (*hashtable));
  c.hashtable = hashtable;
  if (!hashtable)
    return 1;

  grub_disk_read (data->disk, dir->block, GRUB_AFFS_HASHTABLE_OFFSET,
		  data->htsize * sizeof (*hashtable), (char *) hashtable);
  if (grub_errno)
    goto fail;

  /* Create the directory entries for `.' and `..'.  */
  if (grub_affs_create_node (".", dir->block, dir->size, GRUB_FSHELP_DIR, &c))
    return 1;
  if (grub_affs_create_node ("..", dir->parent ? dir->parent : dir->block,
			     dir->size, GRUB_FSHELP_DIR, &c))
    return 1;

  for (i = 0; i < data->htsize; i++)
    {
      enum grub_fshelp_filetype type;
      grub_uint64_t next;

      if (!hashtable[i])
	continue;

      /* Every entry in the hashtable can be chained.  Read the entire
	 chain.  */
      next = grub_be_to_cpu32 (hashtable[i]);

      while (next)
	{
	  grub_disk_read (data->disk, next + data->blocksize - 1,
			  data->blocksize * GRUB_DISK_SECTOR_SIZE
			  - GRUB_AFFS_FILE_LOCATION,
			  sizeof (file), (char *) &file);
	  if (grub_errno)
	    goto fail;

	  file.name[file.namelen] = '\0';

	  if ((int) grub_be_to_cpu32 (file.type) == GRUB_AFFS_FILETYPE_DIR)
	    type = GRUB_FSHELP_REG;
	  else if (grub_be_to_cpu32 (file.type) == GRUB_AFFS_FILETYPE_REG)
	    type = GRUB_FSHELP_DIR;
	  else if (grub_be_to_cpu32 (file.type) == GRUB_AFFS_FILETYPE_SYMLINK)
	    type = GRUB_FSHELP_SYMLINK;
	  else
	    type = GRUB_FSHELP_UNKNOWN;

	  if (grub_affs_create_node ((char *) (file.name), next,
				     grub_be_to_cpu32 (file.size), type, &c))
	    return 1;

	  next = grub_be_to_cpu32 (file.next);
	}
    }

  grub_free (hashtable);
  return 0;

 fail:
  grub_free (c.node);
  grub_free (hashtable);
  return 0;
}