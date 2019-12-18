#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_5__ {int skewBucketLen; TYPE_1__** skewBucket; int /*<<< orphan*/  skewEnabled; } ;
struct TYPE_4__ {int hashvalue; } ;
typedef  TYPE_2__* HashJoinTable ;

/* Variables and functions */
 int INVALID_SKEW_BUCKET_NO ; 

int
ExecHashGetSkewBucket(HashJoinTable hashtable, uint32 hashvalue)
{
	int			bucket;

	/*
	 * Always return INVALID_SKEW_BUCKET_NO if not doing skew optimization (in
	 * particular, this happens after the initial batch is done).
	 */
	if (!hashtable->skewEnabled)
		return INVALID_SKEW_BUCKET_NO;

	/*
	 * Since skewBucketLen is a power of 2, we can do a modulo by ANDing.
	 */
	bucket = hashvalue & (hashtable->skewBucketLen - 1);

	/*
	 * While we have not hit a hole in the hashtable and have not hit the
	 * desired bucket, we have collided with some other hash value, so try the
	 * next bucket location.
	 */
	while (hashtable->skewBucket[bucket] != NULL &&
		   hashtable->skewBucket[bucket]->hashvalue != hashvalue)
		bucket = (bucket + 1) & (hashtable->skewBucketLen - 1);

	/*
	 * Found the desired bucket?
	 */
	if (hashtable->skewBucket[bucket] != NULL)
		return bucket;

	/*
	 * There must not be any hashtable entry for this hash value.
	 */
	return INVALID_SKEW_BUCKET_NO;
}