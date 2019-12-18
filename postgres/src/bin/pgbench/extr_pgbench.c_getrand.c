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
typedef  int int64 ;
struct TYPE_3__ {int /*<<< orphan*/  xseed; } ;
typedef  TYPE_1__ RandomState ;

/* Variables and functions */
 int pg_erand48 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64
getrand(RandomState *random_state, int64 min, int64 max)
{
	/*
	 * Odd coding is so that min and max have approximately the same chance of
	 * being selected as do numbers between them.
	 *
	 * pg_erand48() is thread-safe and concurrent, which is why we use it
	 * rather than random(), which in glibc is non-reentrant, and therefore
	 * protected by a mutex, and therefore a bottleneck on machines with many
	 * CPUs.
	 */
	return min + (int64) ((max - min + 1) * pg_erand48(random_state->xseed));
}