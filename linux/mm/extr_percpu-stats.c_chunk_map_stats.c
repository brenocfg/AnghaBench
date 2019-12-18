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
struct seq_file {int dummy; } ;
struct pcpu_block_md {int first_free; int contig_hint; } ;
struct pcpu_chunk {int end_offset; int start_offset; int nr_alloc; int max_alloc_size; int nr_empty_pop_pages; int free_bytes; int /*<<< orphan*/  alloc_map; int /*<<< orphan*/  bound_map; struct pcpu_block_md chunk_md; } ;

/* Variables and functions */
 int /*<<< orphan*/  P (char*,int) ; 
 int PCPU_MIN_ALLOC_SIZE ; 
 int /*<<< orphan*/  cmpint ; 
 int find_last_bit (int /*<<< orphan*/ ,int) ; 
 int find_next_bit (int /*<<< orphan*/ ,int,int) ; 
 int max (int,int) ; 
 int pcpu_chunk_map_bits (struct pcpu_chunk*) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  sort (int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chunk_map_stats(struct seq_file *m, struct pcpu_chunk *chunk,
			    int *buffer)
{
	struct pcpu_block_md *chunk_md = &chunk->chunk_md;
	int i, last_alloc, as_len, start, end;
	int *alloc_sizes, *p;
	/* statistics */
	int sum_frag = 0, max_frag = 0;
	int cur_min_alloc = 0, cur_med_alloc = 0, cur_max_alloc = 0;

	alloc_sizes = buffer;

	/*
	 * find_last_bit returns the start value if nothing found.
	 * Therefore, we must determine if it is a failure of find_last_bit
	 * and set the appropriate value.
	 */
	last_alloc = find_last_bit(chunk->alloc_map,
				   pcpu_chunk_map_bits(chunk) -
				   chunk->end_offset / PCPU_MIN_ALLOC_SIZE - 1);
	last_alloc = test_bit(last_alloc, chunk->alloc_map) ?
		     last_alloc + 1 : 0;

	as_len = 0;
	start = chunk->start_offset / PCPU_MIN_ALLOC_SIZE;

	/*
	 * If a bit is set in the allocation map, the bound_map identifies
	 * where the allocation ends.  If the allocation is not set, the
	 * bound_map does not identify free areas as it is only kept accurate
	 * on allocation, not free.
	 *
	 * Positive values are allocations and negative values are free
	 * fragments.
	 */
	while (start < last_alloc) {
		if (test_bit(start, chunk->alloc_map)) {
			end = find_next_bit(chunk->bound_map, last_alloc,
					    start + 1);
			alloc_sizes[as_len] = 1;
		} else {
			end = find_next_bit(chunk->alloc_map, last_alloc,
					    start + 1);
			alloc_sizes[as_len] = -1;
		}

		alloc_sizes[as_len++] *= (end - start) * PCPU_MIN_ALLOC_SIZE;

		start = end;
	}

	/*
	 * The negative values are free fragments and thus sorting gives the
	 * free fragments at the beginning in largest first order.
	 */
	if (as_len > 0) {
		sort(alloc_sizes, as_len, sizeof(int), cmpint, NULL);

		/* iterate through the unallocated fragments */
		for (i = 0, p = alloc_sizes; *p < 0 && i < as_len; i++, p++) {
			sum_frag -= *p;
			max_frag = max(max_frag, -1 * (*p));
		}

		cur_min_alloc = alloc_sizes[i];
		cur_med_alloc = alloc_sizes[(i + as_len - 1) / 2];
		cur_max_alloc = alloc_sizes[as_len - 1];
	}

	P("nr_alloc", chunk->nr_alloc);
	P("max_alloc_size", chunk->max_alloc_size);
	P("empty_pop_pages", chunk->nr_empty_pop_pages);
	P("first_bit", chunk_md->first_free);
	P("free_bytes", chunk->free_bytes);
	P("contig_bytes", chunk_md->contig_hint * PCPU_MIN_ALLOC_SIZE);
	P("sum_frag", sum_frag);
	P("max_frag", max_frag);
	P("cur_min_alloc", cur_min_alloc);
	P("cur_med_alloc", cur_med_alloc);
	P("cur_max_alloc", cur_max_alloc);
	seq_putc(m, '\n');
}