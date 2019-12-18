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
union ubifs_key {int /*<<< orphan*/ * j32; } ;
typedef  int uint32_t ;
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 int UBIFS_S_KEY_HASH_MASK ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t key_hash_flash(const struct ubifs_info *c, const void *k)
{
	const union ubifs_key *key = k;

	return le32_to_cpu(key->j32[1]) & UBIFS_S_KEY_HASH_MASK;
}