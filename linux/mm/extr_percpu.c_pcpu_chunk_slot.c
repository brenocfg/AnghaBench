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
struct pcpu_block_md {int contig_hint; } ;
struct pcpu_chunk {int free_bytes; struct pcpu_block_md chunk_md; } ;

/* Variables and functions */
 int PCPU_MIN_ALLOC_SIZE ; 
 int pcpu_size_to_slot (int) ; 

__attribute__((used)) static int pcpu_chunk_slot(const struct pcpu_chunk *chunk)
{
	const struct pcpu_block_md *chunk_md = &chunk->chunk_md;

	if (chunk->free_bytes < PCPU_MIN_ALLOC_SIZE ||
	    chunk_md->contig_hint == 0)
		return 0;

	return pcpu_size_to_slot(chunk_md->contig_hint * PCPU_MIN_ALLOC_SIZE);
}