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
typedef  unsigned long u8 ;
struct keyring_index_key {int desc_len; scalar_t__ type; scalar_t__ description; } ;
typedef  int /*<<< orphan*/  chunk ;

/* Variables and functions */
 int ASSOC_ARRAY_KEY_CHUNK_SIZE ; 
 unsigned long hash_key_type_and_desc (struct keyring_index_key const*) ; 

__attribute__((used)) static unsigned long keyring_get_key_chunk(const void *data, int level)
{
	const struct keyring_index_key *index_key = data;
	unsigned long chunk = 0;
	long offset = 0;
	int desc_len = index_key->desc_len, n = sizeof(chunk);

	level /= ASSOC_ARRAY_KEY_CHUNK_SIZE;
	switch (level) {
	case 0:
		return hash_key_type_and_desc(index_key);
	case 1:
		return ((unsigned long)index_key->type << 8) | desc_len;
	case 2:
		if (desc_len == 0)
			return (u8)((unsigned long)index_key->type >>
				    (ASSOC_ARRAY_KEY_CHUNK_SIZE - 8));
		n--;
		offset = 1;
	default:
		offset += sizeof(chunk) - 1;
		offset += (level - 3) * sizeof(chunk);
		if (offset >= desc_len)
			return 0;
		desc_len -= offset;
		if (desc_len > n)
			desc_len = n;
		offset += desc_len;
		do {
			chunk <<= 8;
			chunk |= ((u8*)index_key->description)[--offset];
		} while (--desc_len > 0);

		if (level == 2) {
			chunk <<= 8;
			chunk |= (u8)((unsigned long)index_key->type >>
				      (ASSOC_ARRAY_KEY_CHUNK_SIZE - 8));
		}
		return chunk;
	}
}