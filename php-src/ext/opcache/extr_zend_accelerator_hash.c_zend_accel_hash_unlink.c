#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t zend_ulong ;
struct TYPE_4__ {size_t hash_value; scalar_t__ key_length; struct TYPE_4__* next; int /*<<< orphan*/  indirect; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ zend_accel_hash_entry ;
struct TYPE_5__ {size_t max_num_entries; TYPE_1__** hash_table; int /*<<< orphan*/  num_direct_entries; } ;
typedef  TYPE_2__ zend_accel_hash ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 size_t ZCG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/  root_hash ; 
 size_t zend_inline_hash_func (char const*,scalar_t__) ; 

int zend_accel_hash_unlink(zend_accel_hash *accel_hash, const char *key, uint32_t key_length)
{
    zend_ulong hash_value;
    zend_ulong index;
    zend_accel_hash_entry *entry, *last_entry=NULL;

	hash_value = zend_inline_hash_func(key, key_length);
#ifndef ZEND_WIN32
	hash_value ^= ZCG(root_hash);
#endif
	index = hash_value % accel_hash->max_num_entries;

	entry = accel_hash->hash_table[index];
	while (entry) {
		if (entry->hash_value == hash_value
			&& entry->key_length == key_length
			&& !memcmp(entry->key, key, key_length)) {
			if (!entry->indirect) {
				accel_hash->num_direct_entries--;
			}
			if (last_entry) {
				last_entry->next = entry->next;
			} else {
				accel_hash->hash_table[index] = entry->next;
			}
			return SUCCESS;
		}
		last_entry = entry;
		entry = entry->next;
	}
	return FAILURE;
}