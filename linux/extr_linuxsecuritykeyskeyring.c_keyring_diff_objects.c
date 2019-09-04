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
struct keyring_index_key {unsigned long desc_len; scalar_t__ description; scalar_t__ type; } ;
struct key {struct keyring_index_key index_key; } ;

/* Variables and functions */
 int ASSOC_ARRAY_KEY_CHUNK_SIZE ; 
 int __ffs (unsigned long) ; 
 unsigned long hash_key_type_and_desc (struct keyring_index_key const*) ; 
 struct key* keyring_ptr_to_key (void const*) ; 

__attribute__((used)) static int keyring_diff_objects(const void *object, const void *data)
{
	const struct key *key_a = keyring_ptr_to_key(object);
	const struct keyring_index_key *a = &key_a->index_key;
	const struct keyring_index_key *b = data;
	unsigned long seg_a, seg_b;
	int level, i;

	level = 0;
	seg_a = hash_key_type_and_desc(a);
	seg_b = hash_key_type_and_desc(b);
	if ((seg_a ^ seg_b) != 0)
		goto differ;

	/* The number of bits contributed by the hash is controlled by a
	 * constant in the assoc_array headers.  Everything else thereafter we
	 * can deal with as being machine word-size dependent.
	 */
	level += ASSOC_ARRAY_KEY_CHUNK_SIZE / 8;
	seg_a = a->desc_len;
	seg_b = b->desc_len;
	if ((seg_a ^ seg_b) != 0)
		goto differ;

	/* The next bit may not work on big endian */
	level++;
	seg_a = (unsigned long)a->type;
	seg_b = (unsigned long)b->type;
	if ((seg_a ^ seg_b) != 0)
		goto differ;

	level += sizeof(unsigned long);
	if (a->desc_len == 0)
		goto same;

	i = 0;
	if (((unsigned long)a->description | (unsigned long)b->description) &
	    (sizeof(unsigned long) - 1)) {
		do {
			seg_a = *(unsigned long *)(a->description + i);
			seg_b = *(unsigned long *)(b->description + i);
			if ((seg_a ^ seg_b) != 0)
				goto differ_plus_i;
			i += sizeof(unsigned long);
		} while (i < (a->desc_len & (sizeof(unsigned long) - 1)));
	}

	for (; i < a->desc_len; i++) {
		seg_a = *(unsigned char *)(a->description + i);
		seg_b = *(unsigned char *)(b->description + i);
		if ((seg_a ^ seg_b) != 0)
			goto differ_plus_i;
	}

same:
	return -1;

differ_plus_i:
	level += i;
differ:
	i = level * 8 + __ffs(seg_a ^ seg_b);
	return i;
}