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
typedef  int u16 ;
struct super_block {int dummy; } ;
struct TYPE_2__ {int all_key_count; } ;
struct befs_btree_node {TYPE_1__ head; } ;
typedef  int /*<<< orphan*/  fs16 ;

/* Variables and functions */
 char* befs_bt_keydata (struct befs_btree_node*) ; 
 int /*<<< orphan*/ * befs_bt_keylen_index (struct befs_btree_node*) ; 
 int fs16_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
befs_bt_get_key(struct super_block *sb, struct befs_btree_node *node,
		int index, u16 * keylen)
{
	int prev_key_end;
	char *keystart;
	fs16 *keylen_index;

	if (index < 0 || index > node->head.all_key_count) {
		*keylen = 0;
		return NULL;
	}

	keystart = befs_bt_keydata(node);
	keylen_index = befs_bt_keylen_index(node);

	if (index == 0)
		prev_key_end = 0;
	else
		prev_key_end = fs16_to_cpu(sb, keylen_index[index - 1]);

	*keylen = fs16_to_cpu(sb, keylen_index[index]) - prev_key_end;

	return keystart + prev_key_end;
}