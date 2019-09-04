#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct grub_fshelp_node {int size; int block; int /*<<< orphan*/  parent; int /*<<< orphan*/  data; } ;
struct grub_affs_iterate_dir_closure {int /*<<< orphan*/  hashtable; int /*<<< orphan*/  closure; scalar_t__ (* hook ) (char const*,int,struct grub_fshelp_node*,int /*<<< orphan*/ ) ;TYPE_1__* file; int /*<<< orphan*/  data; struct grub_fshelp_node* node; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  grub_be_to_cpu32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_free (int /*<<< orphan*/ ) ; 
 struct grub_fshelp_node* grub_malloc (int) ; 
 scalar_t__ stub1 (char const*,int,struct grub_fshelp_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
grub_affs_create_node (const char *name, int block,
		       int size, int type,
		       struct grub_affs_iterate_dir_closure *c)
{
  struct grub_fshelp_node *node;

  node = grub_malloc (sizeof (*node));
  c->node = node;
  if (!node)
    {
      grub_free (c->hashtable);
      return 1;
    }

  node->data = c->data;
  node->size = size;
  node->block = block;
  node->parent = grub_be_to_cpu32 (c->file->parent);

  if (c->hook (name, type, node, c->closure))
    {
      grub_free (c->hashtable);
      return 1;
    }
  return 0;
}