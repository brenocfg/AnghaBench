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
typedef  int /*<<< orphan*/  libperf_print_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  _SC_PAGE_SIZE ; 
 int /*<<< orphan*/  __libperf_pr ; 
 int /*<<< orphan*/  page_size ; 
 int /*<<< orphan*/  sysconf (int /*<<< orphan*/ ) ; 

void libperf_init(libperf_print_fn_t fn)
{
	page_size = sysconf(_SC_PAGE_SIZE);
	__libperf_pr = fn;
}