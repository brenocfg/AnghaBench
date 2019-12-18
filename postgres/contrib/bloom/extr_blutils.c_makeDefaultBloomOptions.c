#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bloomLength; int /*<<< orphan*/ * bitSize; } ;
typedef  TYPE_1__ BloomOptions ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_BLOOM_BITS ; 
 int DEFAULT_BLOOM_LENGTH ; 
 int INDEX_MAX_KEYS ; 
 int /*<<< orphan*/  SET_VARSIZE (TYPE_1__*,int) ; 
 int SIGNWORDBITS ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static BloomOptions *
makeDefaultBloomOptions(void)
{
	BloomOptions *opts;
	int			i;

	opts = (BloomOptions *) palloc0(sizeof(BloomOptions));
	/* Convert DEFAULT_BLOOM_LENGTH from # of bits to # of words */
	opts->bloomLength = (DEFAULT_BLOOM_LENGTH + SIGNWORDBITS - 1) / SIGNWORDBITS;
	for (i = 0; i < INDEX_MAX_KEYS; i++)
		opts->bitSize[i] = DEFAULT_BLOOM_BITS;
	SET_VARSIZE(opts, sizeof(BloomOptions));
	return opts;
}