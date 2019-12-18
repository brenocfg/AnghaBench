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
struct pcpu_chunk {int /*<<< orphan*/  nr_pages; } ;

/* Variables and functions */
 int pcpu_nr_pages_to_map_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int pcpu_chunk_map_bits(struct pcpu_chunk *chunk)
{
	return pcpu_nr_pages_to_map_bits(chunk->nr_pages);
}