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

/* Variables and functions */
 unsigned int RIM_CHUNK_SIZE ; 
 scalar_t__ map1 ; 

__attribute__((used)) static inline char *compute_chunk_start_addr(unsigned int thread_id)
{
	char *chunk_start;

	chunk_start = (char *)((unsigned long)map1 +
			       (thread_id * RIM_CHUNK_SIZE));

	return chunk_start;
}