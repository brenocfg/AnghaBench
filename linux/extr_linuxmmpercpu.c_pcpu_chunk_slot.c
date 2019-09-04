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
struct pcpu_chunk {scalar_t__ free_bytes; scalar_t__ contig_bits; } ;

/* Variables and functions */
 scalar_t__ PCPU_MIN_ALLOC_SIZE ; 
 int pcpu_size_to_slot (scalar_t__) ; 

__attribute__((used)) static int pcpu_chunk_slot(const struct pcpu_chunk *chunk)
{
	if (chunk->free_bytes < PCPU_MIN_ALLOC_SIZE || chunk->contig_bits == 0)
		return 0;

	return pcpu_size_to_slot(chunk->free_bytes);
}