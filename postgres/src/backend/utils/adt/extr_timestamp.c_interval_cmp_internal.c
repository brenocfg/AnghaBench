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
typedef  int /*<<< orphan*/  Interval ;
typedef  int /*<<< orphan*/  INT128 ;

/* Variables and functions */
 int int128_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interval_cmp_value (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
interval_cmp_internal(Interval *interval1, Interval *interval2)
{
	INT128		span1 = interval_cmp_value(interval1);
	INT128		span2 = interval_cmp_value(interval2);

	return int128_compare(span1, span2);
}