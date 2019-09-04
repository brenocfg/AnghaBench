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
struct btrfsic_block_hashtable {scalar_t__ table; } ;

/* Variables and functions */
 int BTRFSIC_BLOCK_HASHTABLE_SIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (scalar_t__) ; 

__attribute__((used)) static void btrfsic_block_hashtable_init(struct btrfsic_block_hashtable *h)
{
	int i;

	for (i = 0; i < BTRFSIC_BLOCK_HASHTABLE_SIZE; i++)
		INIT_LIST_HEAD(h->table + i);
}