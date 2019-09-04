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
struct fib_kuid_range {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 scalar_t__ uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uid_range_set(struct fib_kuid_range *range)
{
	return uid_valid(range->start) && uid_valid(range->end);
}