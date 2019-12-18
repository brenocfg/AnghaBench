#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* name; int /*<<< orphan*/  parent; } ;
struct grub_hfsplus_key_internal {TYPE_1__ catkey; } ;
struct grub_hfsplus_iterate_dir_closure {int (* hook ) (char const*,int,TYPE_3__*,void*) ;int ret; void* closure; TYPE_3__* dir; } ;
struct grub_hfsplus_btnode {int dummy; } ;
typedef  TYPE_3__* grub_fshelp_node_t ;
struct TYPE_9__ {TYPE_2__* data; int /*<<< orphan*/  fileid; } ;
struct TYPE_8__ {int /*<<< orphan*/  catalog_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  grub_free (struct grub_hfsplus_btnode*) ; 
 int /*<<< orphan*/  grub_hfsplus_btree_iterate_node (int /*<<< orphan*/ *,struct grub_hfsplus_btnode*,int,int /*<<< orphan*/ ,struct grub_hfsplus_iterate_dir_closure*) ; 
 scalar_t__ grub_hfsplus_btree_search (int /*<<< orphan*/ *,struct grub_hfsplus_key_internal*,int /*<<< orphan*/ ,struct grub_hfsplus_btnode**,int*) ; 
 int /*<<< orphan*/  grub_hfsplus_cmp_catkey ; 
 int /*<<< orphan*/  list_nodes ; 

__attribute__((used)) static int
grub_hfsplus_iterate_dir (grub_fshelp_node_t dir,
			  int (*hook) (const char *filename,
				       enum grub_fshelp_filetype filetype,
				       grub_fshelp_node_t node,
				       void *closure),
			  void *closure)
{
  struct grub_hfsplus_key_internal intern;
  struct grub_hfsplus_btnode *node = NULL;
  int ptr = 0;
  struct grub_hfsplus_iterate_dir_closure c;

  /* Create a key that points to the first entry in the directory.  */
  intern.catkey.parent = dir->fileid;
  intern.catkey.name = "";

  /* First lookup the first entry.  */
  if (grub_hfsplus_btree_search (&dir->data->catalog_tree, &intern,
				 grub_hfsplus_cmp_catkey, &node, &ptr))
    return 0;

  c.dir = dir;
  c.hook = hook;
  c.closure = closure;
  c.ret = 0;
  /* Iterate over all entries in this directory.  */
  grub_hfsplus_btree_iterate_node (&dir->data->catalog_tree, node, ptr,
				   list_nodes, &c);

  grub_free (node);

  return c.ret;
}