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
struct timespec {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int test_failed ; 
 scalar_t__ timespec_to_us64 (struct timespec*) ; 
 struct timespec ts_usr ; 

__attribute__((used)) static void validate_timestamp(struct timespec *cur, int min_delay)
{
	int max_delay = min_delay + 500 /* processing time upper bound */;
	int64_t cur64, start64;

	cur64 = timespec_to_us64(cur);
	start64 = timespec_to_us64(&ts_usr);

	if (cur64 < start64 + min_delay || cur64 > start64 + max_delay) {
		fprintf(stderr, "ERROR: delay %lu expected between %d and %d\n",
				cur64 - start64, min_delay, max_delay);
		test_failed = true;
	}
}