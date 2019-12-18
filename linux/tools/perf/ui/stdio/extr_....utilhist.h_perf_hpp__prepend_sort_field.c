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
struct perf_hpp_fmt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_hpp_list ; 
 int /*<<< orphan*/  perf_hpp_list__prepend_sort_field (int /*<<< orphan*/ *,struct perf_hpp_fmt*) ; 

__attribute__((used)) static inline void perf_hpp__prepend_sort_field(struct perf_hpp_fmt *format)
{
	perf_hpp_list__prepend_sort_field(&perf_hpp_list, format);
}