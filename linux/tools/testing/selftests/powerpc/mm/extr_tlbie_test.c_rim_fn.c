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
typedef  scalar_t__ chunk_start ;

/* Variables and functions */
 int RIM_CHUNK_SIZE ; 
 char* compute_chunk_start_addr (unsigned int) ; 
 unsigned int compute_store_pattern (unsigned int,unsigned int*,unsigned int) ; 
 int corruption_found ; 
 int /*<<< orphan*/  dcbf (unsigned int volatile*) ; 
 int /*<<< orphan*/  set_segv_handler () ; 
 scalar_t__ timeout ; 
 int /*<<< orphan*/  verify_chunk (unsigned int,unsigned int*,unsigned int,unsigned int) ; 

__attribute__((used)) static void *rim_fn(void *arg)
{
	unsigned int tid = *((unsigned int *)arg);

	int size = RIM_CHUNK_SIZE;
	char *chunk_start = compute_chunk_start_addr(tid);

	unsigned int prev_sweep_id;
	unsigned int cur_sweep_id = 0;

	/* word access */
	unsigned int pattern = cur_sweep_id;
	unsigned int *pattern_ptr = &pattern;
	unsigned int *w_ptr, read_data;

	set_segv_handler();

	/*
	 * Let us initialize the chunk:
	 *
	 * Each word-aligned address addr in the chunk,
	 * is initialized to :
	 *    |-------------------------------------------------|
	 *    | tid   | word_offset(addr) |         0           |
	 *    |-------------------------------------------------|
	 */
	for (w_ptr = (unsigned int *)chunk_start;
	     (unsigned long)w_ptr < (unsigned long)(chunk_start) + size;
	     w_ptr++) {

		*pattern_ptr = compute_store_pattern(tid, w_ptr, cur_sweep_id);
		*w_ptr = *pattern_ptr;
	}

	while (!corruption_found && !timeout) {
		prev_sweep_id = cur_sweep_id;
		cur_sweep_id = cur_sweep_id + 1;

		for (w_ptr = (unsigned int *)chunk_start;
		     (unsigned long)w_ptr < (unsigned long)(chunk_start) + size;
		     w_ptr++)  {
			unsigned int old_pattern;

			/*
			 * Compute the pattern that we would have
			 * stored at this location in the previous
			 * sweep.
			 */
			old_pattern = compute_store_pattern(tid, w_ptr, prev_sweep_id);

			/*
			 * FLUSH:Ensure that we flush the contents of
			 *       the cache before loading
			 */
			dcbf((volatile unsigned int*)w_ptr); //Flush

			/* LOAD: Read the value */
			read_data = *w_ptr; //Load

			/*
			 * COMPARE: Is it the same as what we had stored
			 *          in the previous sweep ? It better be!
			 */
			if (read_data != old_pattern) {
				/* No it isn't! Tell everyone */
				corruption_found = 1;
			}

			/*
			 * Before performing a store, let us check if
			 * any rim_thread has found a corruption.
			 */
			if (corruption_found || timeout) {
				/*
				 * Yes. Someone (including us!) has found
				 * a corruption :(
				 *
				 * Let us verify that our chunk is
				 * correct.
				 */
				/* But first, let us allow the dust to settle down! */
				verify_chunk(tid, w_ptr, cur_sweep_id, prev_sweep_id);

				return 0;
			}

			/*
			 * Compute the new pattern that we are going
			 * to write to this location
			 */
			*pattern_ptr = compute_store_pattern(tid, w_ptr, cur_sweep_id);

			/*
			 * STORE: Now let us write this pattern into
			 *        the location
			 */
			*w_ptr = *pattern_ptr;
		}
	}

	return NULL;
}