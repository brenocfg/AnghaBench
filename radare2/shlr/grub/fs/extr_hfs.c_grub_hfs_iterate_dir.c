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
struct grub_hfs_iterate_dir_closure {unsigned int dir; int (* hook ) (struct grub_hfs_record*,void*) ;int next; int found; scalar_t__ isleaf; void* closure; struct grub_hfs_catalog_key* key; } ;
struct grub_hfs_data {int dummy; } ;
struct grub_hfs_catalog_key {char* member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int grub_uint32_t ;
typedef  int /*<<< orphan*/  grub_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  grub_cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_hfs_iterate_dir_it_dir ; 
 int /*<<< orphan*/  grub_hfs_iterate_dir_node_found ; 
 scalar_t__ grub_hfs_iterate_records (struct grub_hfs_data*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct grub_hfs_iterate_dir_closure*) ; 

__attribute__((used)) static grub_err_t
grub_hfs_iterate_dir (struct grub_hfs_data *data, grub_uint32_t root_idx,
		      unsigned int dir,
		      int (*hook) (struct grub_hfs_record *, void *closure),
		      void *closure)
{
  /* The lowest key possible with DIR as root directory.  */
  struct grub_hfs_catalog_key key = {0, grub_cpu_to_be32 (dir), 0, ""};
  struct grub_hfs_iterate_dir_closure c;

  c.key = &key;
  c.dir = dir;
  c.hook = hook;
  c.closure = closure;
  c.isleaf = 0;
  c.next = 0;
  do
    {
      c.found = -1;

      if (grub_hfs_iterate_records (data, 0, root_idx, 0,
				    grub_hfs_iterate_dir_node_found, &c))
        return grub_errno;

      if (c.found == -1)
        return 0;

      root_idx = c.found;
    } while (! c.isleaf);

  /* If there was a matching record in this leaf node, continue the
     iteration until the last record was found.  */
  grub_hfs_iterate_records (data, 0, c.next, 1, grub_hfs_iterate_dir_it_dir, &c);
  return grub_errno;
}