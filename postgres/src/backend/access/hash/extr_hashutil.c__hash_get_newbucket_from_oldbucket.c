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
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Bucket ;

/* Variables and functions */
 scalar_t__ CALC_NEW_BUCKET (scalar_t__,scalar_t__) ; 

Bucket
_hash_get_newbucket_from_oldbucket(Relation rel, Bucket old_bucket,
								   uint32 lowmask, uint32 maxbucket)
{
	Bucket		new_bucket;

	new_bucket = CALC_NEW_BUCKET(old_bucket, lowmask);
	if (new_bucket > maxbucket)
	{
		lowmask = lowmask >> 1;
		new_bucket = CALC_NEW_BUCKET(old_bucket, lowmask);
	}

	return new_bucket;
}