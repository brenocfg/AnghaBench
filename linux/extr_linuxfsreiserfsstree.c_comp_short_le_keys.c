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
struct reiserfs_key {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int REISERFS_SHORT_KEY_LEN ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

inline int comp_short_le_keys(const struct reiserfs_key *key1,
			      const struct reiserfs_key *key2)
{
	__u32 *k1_u32, *k2_u32;
	int key_length = REISERFS_SHORT_KEY_LEN;

	k1_u32 = (__u32 *) key1;
	k2_u32 = (__u32 *) key2;
	for (; key_length--; ++k1_u32, ++k2_u32) {
		if (le32_to_cpu(*k1_u32) < le32_to_cpu(*k2_u32))
			return -1;
		if (le32_to_cpu(*k1_u32) > le32_to_cpu(*k2_u32))
			return 1;
	}
	return 0;
}