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
struct perf_hpp_fmt {scalar_t__ (* equal ) (struct perf_hpp_fmt*,struct perf_hpp_fmt*) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (struct perf_hpp_fmt*,struct perf_hpp_fmt*) ; 

__attribute__((used)) static bool fmt_equal(struct perf_hpp_fmt *a, struct perf_hpp_fmt *b)
{
	return a->equal && a->equal(a, b);
}