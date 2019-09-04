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
struct perf_hpp {int dummy; } ;
struct hist_entry {int dummy; } ;

/* Variables and functions */
 int percent_color (struct perf_hpp_fmt*,struct perf_hpp*,struct hist_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percent_st_l1hit ; 

__attribute__((used)) static int
percent_stores_l1hit_color(struct perf_hpp_fmt *fmt, struct perf_hpp *hpp,
			   struct hist_entry *he)
{
	return percent_color(fmt, hpp, he, percent_st_l1hit);
}