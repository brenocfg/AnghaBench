#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct grub_hfsplus_iterate_dir_closure {int (* hook ) (char*,int,struct grub_fshelp_node*,int /*<<< orphan*/ ) ;int ret; int /*<<< orphan*/  closure; TYPE_2__* dir; } ;
struct grub_hfsplus_catkey {int keylen; int namelen; int* name; int /*<<< orphan*/  parent; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  extents; } ;
struct grub_hfsplus_catfile {int type; int mode; int /*<<< orphan*/  fileid; TYPE_3__ data; int /*<<< orphan*/  mtime; } ;
struct grub_fshelp_node {scalar_t__ fileid; int /*<<< orphan*/  size; scalar_t__ mtime; int /*<<< orphan*/  extents; TYPE_1__* data; } ;
typedef  int /*<<< orphan*/  grub_uint8_t ;
typedef  enum grub_fshelp_filetype { ____Placeholder_grub_fshelp_filetype } grub_fshelp_filetype ;
struct TYPE_5__ {scalar_t__ fileid; TYPE_1__* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  case_sensitive; } ;

/* Variables and functions */
 int GRUB_FSHELP_CASE_INSENSITIVE ; 
 int GRUB_FSHELP_DIR ; 
 int GRUB_FSHELP_REG ; 
 int GRUB_FSHELP_SYMLINK ; 
 int GRUB_FSHELP_UNKNOWN ; 
 int GRUB_HFSPLUS_FILEMODE_MASK ; 
 int GRUB_HFSPLUS_FILEMODE_REG ; 
 int GRUB_HFSPLUS_FILEMODE_SYMLINK ; 
 int GRUB_HFSPLUS_FILETYPE_DIR ; 
 int GRUB_HFSPLUS_FILETYPE_REG ; 
 int grub_be_to_cpu16 (int) ; 
 scalar_t__ grub_be_to_cpu32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_be_to_cpu64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_free (char*) ; 
 void* grub_malloc (int) ; 
 int /*<<< orphan*/  grub_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int grub_strlen (char*) ; 
 int /*<<< orphan*/  grub_utf16_to_utf8 (int /*<<< orphan*/ *,int*,int) ; 
 int stub1 (char*,int,struct grub_fshelp_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
list_nodes (void *record, void *closure)
{
  struct grub_hfsplus_iterate_dir_closure *c = closure;
  struct grub_hfsplus_catkey *catkey;
  char *filename;
  int i;
  struct grub_fshelp_node *node;
  struct grub_hfsplus_catfile *fileinfo;
  enum grub_fshelp_filetype type = GRUB_FSHELP_UNKNOWN;

  catkey = (struct grub_hfsplus_catkey *) record;

  fileinfo =
    (struct grub_hfsplus_catfile *) ((char *) record
				     + grub_be_to_cpu16 (catkey->keylen)
				     + 2 + (grub_be_to_cpu16(catkey->keylen)
					    % 2));

  /* Stop iterating when the last directory entry is found.  */
  if (grub_be_to_cpu32 (catkey->parent) != c->dir->fileid)
    return 1;

  /* Determine the type of the node that is found.  */
  if (grub_be_to_cpu16 (fileinfo->type) == GRUB_HFSPLUS_FILETYPE_REG)
    {
      int mode = (grub_be_to_cpu16 (fileinfo->mode)
		  & GRUB_HFSPLUS_FILEMODE_MASK);

      if (mode == GRUB_HFSPLUS_FILEMODE_REG)
	type = GRUB_FSHELP_REG;
      else if (mode == GRUB_HFSPLUS_FILEMODE_SYMLINK)
	type = GRUB_FSHELP_SYMLINK;
      else
	type = GRUB_FSHELP_UNKNOWN;
    }
  else if (grub_be_to_cpu16 (fileinfo->type) == GRUB_HFSPLUS_FILETYPE_DIR)
    type = GRUB_FSHELP_DIR;

  if (type == GRUB_FSHELP_UNKNOWN)
    return 0;

  /* Make sure the byte order of the UTF16 string is correct.  */
  for (i = 0; i < grub_be_to_cpu16 (catkey->namelen); i++)
    {
      catkey->name[i] = grub_be_to_cpu16 (catkey->name[i]);

      /* If the name is obviously invalid, skip this node.  */
      if (catkey->name[i] == 0)
	return 0;
    }

  filename = grub_malloc (grub_be_to_cpu16 (catkey->namelen) + 1);
  if (! filename)
    return 0;

  if (! grub_utf16_to_utf8 ((grub_uint8_t *) filename, catkey->name,
			    grub_be_to_cpu16 (catkey->namelen)))
    {
      grub_free (filename);
      return 0;
    }

  filename[grub_be_to_cpu16 (catkey->namelen)] = '\0';

  /* Restore the byte order to what it was previously.  */
  for (i = 0; i < grub_be_to_cpu16 (catkey->namelen); i++)
    catkey->name[i] = grub_be_to_cpu16 (catkey->name[i]);

  /* hfs+ is case insensitive.  */
  if (! c->dir->data->case_sensitive)
    type |= GRUB_FSHELP_CASE_INSENSITIVE;

  /* Only accept valid nodes.  */
  if (grub_strlen (filename) == grub_be_to_cpu16 (catkey->namelen))
    {
      /* A valid node is found; setup the node and call the
	 callback function.  */
      node = grub_malloc (sizeof (*node));
      node->data = c->dir->data;

      grub_memcpy (node->extents, fileinfo->data.extents,
		   sizeof (node->extents));
      node->mtime = grub_be_to_cpu32 (fileinfo->mtime) - 2082844800;
      node->size = grub_be_to_cpu64 (fileinfo->data.size);
      node->fileid = grub_be_to_cpu32 (fileinfo->fileid);

      if (c->hook == NULL)
        c->ret = 0;
      else
        c->ret = c->hook (filename, type, node, c->closure);
    }

  grub_free (filename);

  return c->ret;
}