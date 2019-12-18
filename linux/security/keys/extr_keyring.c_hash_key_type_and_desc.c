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
typedef  int u64 ;
typedef  int u32 ;
struct keyring_index_key {char* description; int desc_len; unsigned long hash; int /*<<< orphan*/ * type; scalar_t__ domain_tag; } ;

/* Variables and functions */
 unsigned long ASSOC_ARRAY_FAN_MASK ; 
 int ASSOC_ARRAY_KEY_CHUNK_SIZE ; 
 unsigned int ASSOC_ARRAY_LEVEL_STEP ; 
 int /*<<< orphan*/  key_type_keyring ; 
 int /*<<< orphan*/  memcpy (int*,char const*,int) ; 
 int mult_64x32_and_fold (int,int) ; 

__attribute__((used)) static void hash_key_type_and_desc(struct keyring_index_key *index_key)
{
	const unsigned level_shift = ASSOC_ARRAY_LEVEL_STEP;
	const unsigned long fan_mask = ASSOC_ARRAY_FAN_MASK;
	const char *description = index_key->description;
	unsigned long hash, type;
	u32 piece;
	u64 acc;
	int n, desc_len = index_key->desc_len;

	type = (unsigned long)index_key->type;
	acc = mult_64x32_and_fold(type, desc_len + 13);
	acc = mult_64x32_and_fold(acc, 9207);
	piece = (unsigned long)index_key->domain_tag;
	acc = mult_64x32_and_fold(acc, piece);
	acc = mult_64x32_and_fold(acc, 9207);

	for (;;) {
		n = desc_len;
		if (n <= 0)
			break;
		if (n > 4)
			n = 4;
		piece = 0;
		memcpy(&piece, description, n);
		description += n;
		desc_len -= n;
		acc = mult_64x32_and_fold(acc, piece);
		acc = mult_64x32_and_fold(acc, 9207);
	}

	/* Fold the hash down to 32 bits if need be. */
	hash = acc;
	if (ASSOC_ARRAY_KEY_CHUNK_SIZE == 32)
		hash ^= acc >> 32;

	/* Squidge all the keyrings into a separate part of the tree to
	 * ordinary keys by making sure the lowest level segment in the hash is
	 * zero for keyrings and non-zero otherwise.
	 */
	if (index_key->type != &key_type_keyring && (hash & fan_mask) == 0)
		hash |= (hash >> (ASSOC_ARRAY_KEY_CHUNK_SIZE - level_shift)) | 1;
	else if (index_key->type == &key_type_keyring && (hash & fan_mask) != 0)
		hash = (hash + (hash << level_shift)) & ~fan_mask;
	index_key->hash = hash;
}