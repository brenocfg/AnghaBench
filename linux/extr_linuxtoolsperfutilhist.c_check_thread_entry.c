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
 scalar_t__ perf_hpp__is_comm_entry (struct perf_hpp_fmt*) ; 
 scalar_t__ perf_hpp__is_thread_entry (struct perf_hpp_fmt*) ; 

__attribute__((used)) static bool check_thread_entry(struct perf_hpp_fmt *fmt)
{
	return perf_hpp__is_thread_entry(fmt) || perf_hpp__is_comm_entry(fmt);
}