#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
union perf_event {TYPE_1__ header; } ;
struct jit_buf_desc {int /*<<< orphan*/  bytes_written; int /*<<< orphan*/  output; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ perf_data__write (int /*<<< orphan*/ ,union perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jit_inject_event(struct jit_buf_desc *jd, union perf_event *event)
{
	ssize_t size;

	size = perf_data__write(jd->output, event, event->header.size);
	if (size < 0)
		return -1;

	jd->bytes_written += size;
	return 0;
}