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
struct rhashtable_params {int nelem_hint; scalar_t__ min_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_DEFAULT_SIZE ; 
 size_t max (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  roundup_pow_of_two (int) ; 

__attribute__((used)) static size_t rounded_hashtable_size(const struct rhashtable_params *params)
{
	size_t retsize;

	if (params->nelem_hint)
		retsize = max(roundup_pow_of_two(params->nelem_hint * 4 / 3),
			      (unsigned long)params->min_size);
	else
		retsize = max(HASH_DEFAULT_SIZE,
			      (unsigned long)params->min_size);

	return retsize;
}