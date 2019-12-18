#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kvp_record {int /*<<< orphan*/  key; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {int num_records; int num_blocks; struct kvp_record* records; } ;

/* Variables and functions */
 int ENTRIES_PER_BLOCK ; 
 int HV_KVP_EXCHANGE_MAX_KEY_SIZE ; 
 int HV_KVP_EXCHANGE_MAX_VALUE_SIZE ; 
 TYPE_1__* kvp_file_info ; 
 int /*<<< orphan*/  kvp_update_file (int) ; 
 int /*<<< orphan*/  kvp_update_mem_state (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 struct kvp_record* realloc (struct kvp_record*,int) ; 

__attribute__((used)) static int kvp_key_add_or_modify(int pool, const __u8 *key, int key_size,
				 const __u8 *value, int value_size)
{
	int i;
	int num_records;
	struct kvp_record *record;
	int num_blocks;

	if ((key_size > HV_KVP_EXCHANGE_MAX_KEY_SIZE) ||
		(value_size > HV_KVP_EXCHANGE_MAX_VALUE_SIZE))
		return 1;

	/*
	 * First update the in-memory state.
	 */
	kvp_update_mem_state(pool);

	num_records = kvp_file_info[pool].num_records;
	record = kvp_file_info[pool].records;
	num_blocks = kvp_file_info[pool].num_blocks;

	for (i = 0; i < num_records; i++) {
		if (memcmp(key, record[i].key, key_size))
			continue;
		/*
		 * Found a match; just update the value -
		 * this is the modify case.
		 */
		memcpy(record[i].value, value, value_size);
		kvp_update_file(pool);
		return 0;
	}

	/*
	 * Need to add a new entry;
	 */
	if (num_records == (ENTRIES_PER_BLOCK * num_blocks)) {
		/* Need to allocate a larger array for reg entries. */
		record = realloc(record, sizeof(struct kvp_record) *
			 ENTRIES_PER_BLOCK * (num_blocks + 1));

		if (record == NULL)
			return 1;
		kvp_file_info[pool].num_blocks++;

	}
	memcpy(record[i].value, value, value_size);
	memcpy(record[i].key, key, key_size);
	kvp_file_info[pool].records = record;
	kvp_file_info[pool].num_records++;
	kvp_update_file(pool);
	return 0;
}