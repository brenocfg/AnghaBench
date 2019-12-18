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
struct perf_session {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __print_page_alloc_result (struct perf_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __print_page_caller_result (struct perf_session*,int /*<<< orphan*/ ) ; 
 scalar_t__ alloc_flag ; 
 int /*<<< orphan*/  alloc_lines ; 
 scalar_t__ caller_flag ; 
 int /*<<< orphan*/  caller_lines ; 
 int /*<<< orphan*/  print_gfp_flags () ; 
 int /*<<< orphan*/  print_page_summary () ; 

__attribute__((used)) static void print_page_result(struct perf_session *session)
{
	if (caller_flag || alloc_flag)
		print_gfp_flags();
	if (caller_flag)
		__print_page_caller_result(session, caller_lines);
	if (alloc_flag)
		__print_page_alloc_result(session, alloc_lines);
	print_page_summary();
}