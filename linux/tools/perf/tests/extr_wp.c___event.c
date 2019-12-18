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
struct perf_event_attr {int /*<<< orphan*/  bp_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  get__perf_event_attr (struct perf_event_attr*,int,void*,unsigned long) ; 
 int /*<<< orphan*/  perf_event_open_cloexec_flag () ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int sys_perf_event_open (struct perf_event_attr*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __event(int wp_type, void *wp_addr, unsigned long wp_len)
{
	int fd;
	struct perf_event_attr attr;

	get__perf_event_attr(&attr, wp_type, wp_addr, wp_len);
	fd = sys_perf_event_open(&attr, 0, -1, -1,
				 perf_event_open_cloexec_flag());
	if (fd < 0)
		pr_debug("failed opening event %x\n", attr.bp_type);

	return fd;
}