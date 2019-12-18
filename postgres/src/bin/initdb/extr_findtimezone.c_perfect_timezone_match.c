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
struct tztry {scalar_t__ n_test_times; } ;

/* Variables and functions */
 scalar_t__ score_timezone (char const*,struct tztry*) ; 

__attribute__((used)) static bool
perfect_timezone_match(const char *tzname, struct tztry *tt)
{
	return (score_timezone(tzname, tt) == tt->n_test_times);
}