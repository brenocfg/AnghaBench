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
struct rt6_exception_bucket {int dummy; } ;

/* Variables and functions */
 unsigned long FIB6_EXCEPTION_BUCKET_FLUSHED ; 

__attribute__((used)) static bool fib6_nh_excptn_bucket_flushed(struct rt6_exception_bucket *bucket)
{
	unsigned long p = (unsigned long)bucket;

	return !!(p & FIB6_EXCEPTION_BUCKET_FLUSHED);
}