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
struct grub_hfs_record {scalar_t__ data; struct grub_hfs_catalog_key* key; } ;
struct grub_hfs_node {int type; int /*<<< orphan*/  next; } ;
struct grub_hfs_iterate_dir_closure {int isleaf; scalar_t__ dir; int (* hook ) (struct grub_hfs_record*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  closure; scalar_t__ next; scalar_t__ found; scalar_t__ key; } ;
struct grub_hfs_catalog_key {scalar_t__ strlen; int /*<<< orphan*/  parent_dir; } ;
typedef  int /*<<< orphan*/  grub_uint32_t ;

/* Variables and functions */
 scalar_t__ grub_be_to_cpu32 (int /*<<< orphan*/ ) ; 
 scalar_t__ grub_hfs_cmp_catkeys (struct grub_hfs_catalog_key*,void*) ; 
 int stub1 (struct grub_hfs_record*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
grub_hfs_iterate_dir_node_found (struct grub_hfs_node *hnd,
				 struct grub_hfs_record *rec,
				 void *closure)
{
  struct grub_hfs_iterate_dir_closure *c = closure;
  struct grub_hfs_catalog_key *ckey = rec->key;

  if (grub_hfs_cmp_catkeys (rec->key, (void *) c->key) <= 0)
    c->found = grub_be_to_cpu32 (*(grub_uint32_t *) rec->data);

  if (hnd->type == 0xFF && ckey->strlen > 0)
    {
      c->isleaf = 1;
      c->next = grub_be_to_cpu32 (hnd->next);

      /* An entry was found.  */
      if (grub_be_to_cpu32 (ckey->parent_dir) == c->dir)
	return c->hook?c->hook (rec, c->closure): 0;
    }

  return 0;
}