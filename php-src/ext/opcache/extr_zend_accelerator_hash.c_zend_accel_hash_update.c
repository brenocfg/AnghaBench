#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t zend_ulong ;
typedef  scalar_t__ zend_bool ;
struct TYPE_5__ {int indirect; size_t hash_value; scalar_t__ key_length; char const* key; struct TYPE_5__* next; struct TYPE_5__* data; } ;
typedef  TYPE_1__ zend_accel_hash_entry ;
struct TYPE_6__ {size_t max_num_entries; size_t num_entries; TYPE_1__** hash_table; int /*<<< orphan*/  num_direct_entries; TYPE_1__* hash_entries; } ;
typedef  TYPE_2__ zend_accel_hash ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 size_t ZCG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (char const*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  root_hash ; 
 size_t zend_inline_hash_func (char const*,scalar_t__) ; 

zend_accel_hash_entry* zend_accel_hash_update(zend_accel_hash *accel_hash, const char *key, uint32_t key_length, zend_bool indirect, void *data)
{
	zend_ulong hash_value;
	zend_ulong index;
	zend_accel_hash_entry *entry;
	zend_accel_hash_entry *indirect_bucket = NULL;

	if (indirect) {
		indirect_bucket = (zend_accel_hash_entry*)data;
		while (indirect_bucket->indirect) {
			indirect_bucket = (zend_accel_hash_entry*)indirect_bucket->data;
		}
	}

	hash_value = zend_inline_hash_func(key, key_length);
#ifndef ZEND_WIN32
	hash_value ^= ZCG(root_hash);
#endif
	index = hash_value % accel_hash->max_num_entries;

	/* try to see if the element already exists in the hash */
	entry = accel_hash->hash_table[index];
	while (entry) {
		if (entry->hash_value == hash_value
			&& entry->key_length == key_length
			&& !memcmp(entry->key, key, key_length)) {

			if (entry->indirect) {
				if (indirect_bucket) {
					entry->data = indirect_bucket;
				} else {
					((zend_accel_hash_entry*)entry->data)->data = data;
				}
			} else {
				if (indirect_bucket) {
					accel_hash->num_direct_entries--;
					entry->data = indirect_bucket;
					entry->indirect = 1;
				} else {
					entry->data = data;
				}
			}
			return entry;
		}
		entry = entry->next;
	}

	/* Does not exist, add a new entry */
	if (accel_hash->num_entries == accel_hash->max_num_entries) {
		return NULL;
	}

	entry = &accel_hash->hash_entries[accel_hash->num_entries++];
	if (indirect) {
		entry->data = indirect_bucket;
		entry->indirect = 1;
	} else {
		accel_hash->num_direct_entries++;
		entry->data = data;
		entry->indirect = 0;
	}
	entry->hash_value = hash_value;
	entry->key = key;
	entry->key_length = key_length;
	entry->next = accel_hash->hash_table[index];
	accel_hash->hash_table[index] = entry;
	return entry;
}