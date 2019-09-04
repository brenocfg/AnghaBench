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
typedef  int uint32_t ;

/* Variables and functions */
 int UBIFS_S_KEY_HASH_MASK ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline uint32_t key_mask_hash(uint32_t hash)
{
	hash &= UBIFS_S_KEY_HASH_MASK;
	if (unlikely(hash <= 2))
		hash += 3;
	return hash;
}