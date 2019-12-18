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
struct merkle_tree_params {unsigned int log_arity; unsigned int* level_start; unsigned int log_blocksize; } ;
typedef  unsigned int pgoff_t ;

/* Variables and functions */

__attribute__((used)) static void hash_at_level(const struct merkle_tree_params *params,
			  pgoff_t dindex, unsigned int level, pgoff_t *hindex,
			  unsigned int *hoffset)
{
	pgoff_t position;

	/* Offset of the hash within the level's region, in hashes */
	position = dindex >> (level * params->log_arity);

	/* Index of the hash block in the tree overall */
	*hindex = params->level_start[level] + (position >> params->log_arity);

	/* Offset of the wanted hash (in bytes) within the hash block */
	*hoffset = (position & ((1 << params->log_arity) - 1)) <<
		   (params->log_blocksize - params->log_arity);
}