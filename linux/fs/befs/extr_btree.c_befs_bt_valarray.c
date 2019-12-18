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
struct TYPE_2__ {int all_key_count; } ;
struct befs_btree_node {TYPE_1__ head; } ;
typedef  int /*<<< orphan*/  fs64 ;
typedef  int /*<<< orphan*/  fs16 ;

/* Variables and functions */
 scalar_t__ befs_bt_keylen_index (struct befs_btree_node*) ; 

__attribute__((used)) static fs64 *
befs_bt_valarray(struct befs_btree_node *node)
{
	void *keylen_index_start = (void *) befs_bt_keylen_index(node);
	size_t keylen_index_size = node->head.all_key_count * sizeof (fs16);

	return (fs64 *) (keylen_index_start + keylen_index_size);
}