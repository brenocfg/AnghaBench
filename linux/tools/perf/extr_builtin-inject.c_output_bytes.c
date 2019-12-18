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
struct perf_inject {int /*<<< orphan*/  bytes_written; int /*<<< orphan*/  output; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int errno ; 
 scalar_t__ perf_data__write (int /*<<< orphan*/ *,void*,size_t) ; 

__attribute__((used)) static int output_bytes(struct perf_inject *inject, void *buf, size_t sz)
{
	ssize_t size;

	size = perf_data__write(&inject->output, buf, sz);
	if (size < 0)
		return -errno;

	inject->bytes_written += size;
	return 0;
}