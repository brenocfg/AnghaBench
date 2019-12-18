#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_accel_hash_entry ;
struct TYPE_3__ {size_t max_num_entries; void* hash_table; void* hash_entries; scalar_t__ num_direct_entries; scalar_t__ num_entries; } ;
typedef  TYPE_1__ zend_accel_hash ;
typedef  size_t uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEL_LOG_FATAL ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 size_t num_prime_numbers ; 
 size_t* prime_numbers ; 
 int /*<<< orphan*/  zend_accel_error (int /*<<< orphan*/ ,char*) ; 
 void* zend_shared_alloc (int) ; 

void zend_accel_hash_init(zend_accel_hash *accel_hash, uint32_t hash_size)
{
	uint32_t i;

	for (i=0; i<num_prime_numbers; i++) {
		if (hash_size <= prime_numbers[i]) {
			hash_size = prime_numbers[i];
			break;
		}
	}

	accel_hash->num_entries = 0;
	accel_hash->num_direct_entries = 0;
	accel_hash->max_num_entries = hash_size;

	/* set up hash pointers table */
	accel_hash->hash_table = zend_shared_alloc(sizeof(zend_accel_hash_entry *)*accel_hash->max_num_entries);
	if (!accel_hash->hash_table) {
		zend_accel_error(ACCEL_LOG_FATAL, "Insufficient shared memory!");
		return;
	}

	/* set up hash values table */
	accel_hash->hash_entries = zend_shared_alloc(sizeof(zend_accel_hash_entry)*accel_hash->max_num_entries);
	if (!accel_hash->hash_entries) {
		zend_accel_error(ACCEL_LOG_FATAL, "Insufficient shared memory!");
		return;
	}
	memset(accel_hash->hash_table, 0, sizeof(zend_accel_hash_entry *)*accel_hash->max_num_entries);
}