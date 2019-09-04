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
typedef  scalar_t__ u32 ;
struct log_group {int /*<<< orphan*/ * ent; } ;
struct arena_info {scalar_t__ nfree; int* log_index; } ;

/* Variables and functions */
 int ENXIO ; 
 int btt_log_group_read (struct arena_info*,scalar_t__,struct log_group*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ent_is_padding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_dev (struct arena_info*) ; 

__attribute__((used)) static int log_set_indices(struct arena_info *arena)
{
	bool idx_set = false, initial_state = true;
	int ret, log_index[2] = {-1, -1};
	u32 i, j, next_idx = 0;
	struct log_group log;
	u32 pad_count = 0;

	for (i = 0; i < arena->nfree; i++) {
		ret = btt_log_group_read(arena, i, &log);
		if (ret < 0)
			return ret;

		for (j = 0; j < 4; j++) {
			if (!idx_set) {
				if (ent_is_padding(&log.ent[j])) {
					pad_count++;
					continue;
				} else {
					/* Skip if index has been recorded */
					if ((next_idx == 1) &&
						(j == log_index[0]))
						continue;
					/* valid entry, record index */
					log_index[next_idx] = j;
					next_idx++;
				}
				if (next_idx == 2) {
					/* two valid entries found */
					idx_set = true;
				} else if (next_idx > 2) {
					/* too many valid indices */
					return -ENXIO;
				}
			} else {
				/*
				 * once the indices have been set, just verify
				 * that all subsequent log groups are either in
				 * their initial state or follow the same
				 * indices.
				 */
				if (j == log_index[0]) {
					/* entry must be 'valid' */
					if (ent_is_padding(&log.ent[j]))
						return -ENXIO;
				} else if (j == log_index[1]) {
					;
					/*
					 * log_index[1] can be padding if the
					 * lane never got used and it is still
					 * in the initial state (three 'padding'
					 * entries)
					 */
				} else {
					/* entry must be invalid (padding) */
					if (!ent_is_padding(&log.ent[j]))
						return -ENXIO;
				}
			}
		}
		/*
		 * If any of the log_groups have more than one valid,
		 * non-padding entry, then the we are no longer in the
		 * initial_state
		 */
		if (pad_count < 3)
			initial_state = false;
		pad_count = 0;
	}

	if (!initial_state && !idx_set)
		return -ENXIO;

	/*
	 * If all the entries in the log were in the initial state,
	 * assume new padding scheme
	 */
	if (initial_state)
		log_index[1] = 1;

	/*
	 * Only allow the known permutations of log/padding indices,
	 * i.e. (0, 1), and (0, 2)
	 */
	if ((log_index[0] == 0) && ((log_index[1] == 1) || (log_index[1] == 2)))
		; /* known index possibilities */
	else {
		dev_err(to_dev(arena), "Found an unknown padding scheme\n");
		return -ENXIO;
	}

	arena->log_index[0] = log_index[0];
	arena->log_index[1] = log_index[1];
	dev_dbg(to_dev(arena), "log_index_0 = %d\n", log_index[0]);
	dev_dbg(to_dev(arena), "log_index_1 = %d\n", log_index[1]);
	return 0;
}