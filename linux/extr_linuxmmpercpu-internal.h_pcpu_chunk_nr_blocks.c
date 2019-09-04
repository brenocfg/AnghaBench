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
struct pcpu_chunk {int nr_pages; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int PCPU_BITMAP_BLOCK_SIZE ; 

__attribute__((used)) static inline int pcpu_chunk_nr_blocks(struct pcpu_chunk *chunk)
{
	return chunk->nr_pages * PAGE_SIZE / PCPU_BITMAP_BLOCK_SIZE;
}