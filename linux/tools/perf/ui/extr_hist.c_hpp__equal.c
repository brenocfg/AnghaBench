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
struct perf_hpp_fmt {scalar_t__ idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_hpp__is_hpp_entry (struct perf_hpp_fmt*) ; 

__attribute__((used)) static bool hpp__equal(struct perf_hpp_fmt *a, struct perf_hpp_fmt *b)
{
	if (!perf_hpp__is_hpp_entry(a) || !perf_hpp__is_hpp_entry(b))
		return false;

	return a->idx == b->idx;
}