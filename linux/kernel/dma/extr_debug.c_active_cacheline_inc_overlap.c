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
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int ACTIVE_CACHELINE_MAX_OVERLAP ; 
 int /*<<< orphan*/  WARN_ONCE (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int active_cacheline_read_overlap (int /*<<< orphan*/ ) ; 
 int active_cacheline_set_overlap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_fmt (char*) ; 

__attribute__((used)) static void active_cacheline_inc_overlap(phys_addr_t cln)
{
	int overlap = active_cacheline_read_overlap(cln);

	overlap = active_cacheline_set_overlap(cln, ++overlap);

	/* If we overflowed the overlap counter then we're potentially
	 * leaking dma-mappings.  Otherwise, if maps and unmaps are
	 * balanced then this overflow may cause false negatives in
	 * debug_dma_assert_idle() as the cacheline may be marked idle
	 * prematurely.
	 */
	WARN_ONCE(overlap > ACTIVE_CACHELINE_MAX_OVERLAP,
		  pr_fmt("exceeded %d overlapping mappings of cacheline %pa\n"),
		  ACTIVE_CACHELINE_MAX_OVERLAP, &cln);
}