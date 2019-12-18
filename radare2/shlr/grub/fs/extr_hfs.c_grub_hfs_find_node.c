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
struct grub_hfs_find_node_closure {char* key; int type; char* datar; int datalen; int done; int found; scalar_t__ isleaf; } ;
struct grub_hfs_data {int dummy; } ;
typedef  int grub_uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  grub_hfs_find_node_node_found ; 
 scalar_t__ grub_hfs_iterate_records (struct grub_hfs_data*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct grub_hfs_find_node_closure*) ; 

__attribute__((used)) static int
grub_hfs_find_node (struct grub_hfs_data *data, char *key,
		    grub_uint32_t idx, int type, char *datar, int datalen)
{
  struct grub_hfs_find_node_closure c;

  c.key = key;
  c.type = type;
  c.datar = datar;
  c.datalen = datalen;
  c.isleaf = 0;
  c.done = 0;
  do
    {
      c.found = -1;

      if (grub_hfs_iterate_records (data, type, idx, 0,
				    grub_hfs_find_node_node_found, &c)) {
        return 0;
	}

      if (c.found == -1) {
        return 0;
}

      idx = c.found;
    } while (! c.isleaf);

  return c.done;
}