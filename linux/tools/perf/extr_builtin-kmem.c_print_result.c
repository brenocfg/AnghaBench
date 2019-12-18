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
 scalar_t__ kmem_page ; 
 scalar_t__ kmem_slab ; 
 int /*<<< orphan*/  print_page_result (struct perf_session*) ; 
 int /*<<< orphan*/  print_slab_result (struct perf_session*) ; 

__attribute__((used)) static void print_result(struct perf_session *session)
{
	if (kmem_slab)
		print_slab_result(session);
	if (kmem_page)
		print_page_result(session);
}