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
struct grub_hfs_record {scalar_t__ datalen; scalar_t__ data; int /*<<< orphan*/  key; } ;
struct grub_hfs_node {scalar_t__ type; } ;
struct grub_hfs_find_node_closure {scalar_t__ type; int isleaf; int done; scalar_t__ datalen; int /*<<< orphan*/  datar; int /*<<< orphan*/  found; scalar_t__ key; } ;
typedef  int /*<<< orphan*/  grub_uint32_t ;

/* Variables and functions */
 scalar_t__ GRUB_HFS_NODE_LEAF ; 
 int /*<<< orphan*/  grub_be_to_cpu32 (int /*<<< orphan*/ ) ; 
 int grub_hfs_cmp_catkeys (int /*<<< orphan*/ ,void*) ; 
 int grub_hfs_cmp_extkeys (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  grub_memcpy (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
grub_hfs_find_node_node_found (struct grub_hfs_node *hnd,
			       struct grub_hfs_record *rec,
			       void *closure)
{
  struct grub_hfs_find_node_closure *c = closure;
  int cmp = 1;

  if (c->type == 0)
    cmp = grub_hfs_cmp_catkeys (rec->key, (void *) c->key);
  else
    cmp = grub_hfs_cmp_extkeys (rec->key, (void *) c->key);

  /* If the key is smaller or equal to the current node, mark the
     entry.  In case of a non-leaf mode it will be used to lookup
     the rest of the tree.  */
  if (cmp <= 0)
    {
      grub_uint32_t *node = (grub_uint32_t *) rec->data;
      c->found = grub_be_to_cpu32 (*node);
    }
  else /* The key can not be found in the tree. */
    return 1;

  /* Check if this node is a leaf node.  */
  if (hnd->type == GRUB_HFS_NODE_LEAF)
    {
      c->isleaf = 1;

      /* Found it!!!!  */
      if (cmp == 0)
	{
	  c->done = 1;

	  grub_memcpy (c->datar, rec->data,
		       rec->datalen < c->datalen ? rec->datalen : c->datalen);
	  return 1;
	}
    }

  return 0;
}