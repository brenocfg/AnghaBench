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
struct kasan_access_info {size_t access_size; int is_write; unsigned long ip; void* first_bad_addr; void* access_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_trace_on_warning () ; 
 int /*<<< orphan*/  kasan_report_enabled () ; 
 int /*<<< orphan*/  kasan_report_error (struct kasan_access_info*) ; 
 scalar_t__ likely (int) ; 

void kasan_report(unsigned long addr, size_t size,
		bool is_write, unsigned long ip)
{
	struct kasan_access_info info;

	if (likely(!kasan_report_enabled()))
		return;

	disable_trace_on_warning();

	info.access_addr = (void *)addr;
	info.first_bad_addr = (void *)addr;
	info.access_size = size;
	info.is_write = is_write;
	info.ip = ip;

	kasan_report_error(&info);
}