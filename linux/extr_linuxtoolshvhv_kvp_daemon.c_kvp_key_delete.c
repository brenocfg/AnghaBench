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
struct kvp_record {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {int num_records; struct kvp_record* records; } ;

/* Variables and functions */
 TYPE_1__* kvp_file_info ; 
 int /*<<< orphan*/  kvp_update_file (int) ; 
 int /*<<< orphan*/  kvp_update_mem_state (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvp_key_delete(int pool, const __u8 *key, int key_size)
{
	int i;
	int j, k;
	int num_records;
	struct kvp_record *record;

	/*
	 * First update the in-memory state.
	 */
	kvp_update_mem_state(pool);

	num_records = kvp_file_info[pool].num_records;
	record = kvp_file_info[pool].records;

	for (i = 0; i < num_records; i++) {
		if (memcmp(key, record[i].key, key_size))
			continue;
		/*
		 * Found a match; just move the remaining
		 * entries up.
		 */
		if (i == (num_records - 1)) {
			kvp_file_info[pool].num_records--;
			kvp_update_file(pool);
			return 0;
		}

		j = i;
		k = j + 1;
		for (; k < num_records; k++) {
			strcpy(record[j].key, record[k].key);
			strcpy(record[j].value, record[k].value);
			j++;
		}

		kvp_file_info[pool].num_records--;
		kvp_update_file(pool);
		return 0;
	}
	return 1;
}