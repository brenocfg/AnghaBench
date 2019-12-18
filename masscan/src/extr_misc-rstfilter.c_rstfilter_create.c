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
struct ResetFilter {unsigned long long seed; int bucket_count; int bucket_mask; void* buckets; } ;

/* Variables and functions */
 void* CALLOC (int,int) ; 
 int next_pow2 (size_t) ; 

struct ResetFilter *
rstfilter_create(unsigned long long seed, size_t bucket_count)
{
    struct ResetFilter *rf;
    
    rf = CALLOC(1, sizeof(*rf));
    rf->seed = seed;
    rf->bucket_count = next_pow2(bucket_count);
    rf->bucket_mask = rf->bucket_count - 1;
    rf->buckets = CALLOC(rf->bucket_count/2, sizeof(*rf->buckets));
    
    return rf;
}