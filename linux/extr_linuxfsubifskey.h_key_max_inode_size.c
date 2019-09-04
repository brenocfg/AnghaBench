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
struct ubifs_info {int key_fmt; } ;

/* Variables and functions */
 unsigned long long UBIFS_BLOCK_SIZE ; 
#define  UBIFS_SIMPLE_KEY_FMT 128 
 unsigned long long UBIFS_S_KEY_BLOCK_BITS ; 

__attribute__((used)) static inline unsigned long long key_max_inode_size(const struct ubifs_info *c)
{
	switch (c->key_fmt) {
	case UBIFS_SIMPLE_KEY_FMT:
		return (1ULL << UBIFS_S_KEY_BLOCK_BITS) * UBIFS_BLOCK_SIZE;
	default:
		return 0;
	}
}