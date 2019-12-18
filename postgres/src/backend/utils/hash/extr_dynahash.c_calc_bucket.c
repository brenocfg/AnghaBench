#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_3__ {int high_mask; int max_bucket; int low_mask; } ;
typedef  TYPE_1__ HASHHDR ;

/* Variables and functions */

__attribute__((used)) static inline uint32
calc_bucket(HASHHDR *hctl, uint32 hash_val)
{
	uint32		bucket;

	bucket = hash_val & hctl->high_mask;
	if (bucket > hctl->max_bucket)
		bucket = bucket & hctl->low_mask;

	return bucket;
}