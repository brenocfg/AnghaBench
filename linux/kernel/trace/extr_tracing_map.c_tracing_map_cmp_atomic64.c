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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  atomic64_t ;

/* Variables and functions */
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tracing_map_cmp_atomic64(void *val_a, void *val_b)
{
	u64 a = atomic64_read((atomic64_t *)val_a);
	u64 b = atomic64_read((atomic64_t *)val_b);

	return (a > b) ? 1 : ((a < b) ? -1 : 0);
}