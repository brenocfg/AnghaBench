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
struct grub_nilfs2_btree_node {scalar_t__ bn_level; int /*<<< orphan*/  bn_nchildren; } ;
typedef  scalar_t__ grub_uint64_t ;

/* Variables and functions */
 scalar_t__ NILFS_BTREE_LEVEL_NODE_MIN ; 
 int grub_le_to_cpu16 (int /*<<< orphan*/ ) ; 
 scalar_t__ grub_nilfs2_btree_node_get_key (struct grub_nilfs2_btree_node*,int) ; 

__attribute__((used)) static inline int
grub_nilfs2_btree_node_lookup (struct grub_nilfs2_btree_node *node,
			       grub_uint64_t key, int *indexp)
{
  grub_uint64_t nkey;
  int index, low, high, s;

  low = 0;
  high = grub_le_to_cpu16 (node->bn_nchildren) - 1;
  index = 0;
  s = 0;
  while (low <= high)
    {
      index = (low + high) / 2;
      nkey = grub_nilfs2_btree_node_get_key (node, index);
      if (nkey == key)
	{
	  *indexp = index;
	  return 1;
	}
      else if (nkey < key)
	{
	  low = index + 1;
	  s = -1;
	}
      else
	{
	  high = index - 1;
	  s = 1;
	}
    }

  if (node->bn_level > NILFS_BTREE_LEVEL_NODE_MIN)
    {
      if (s > 0 && index > 0)
	index--;
    }
  else if (s < 0)
    index++;

  *indexp = index;
  return s == 0;
}