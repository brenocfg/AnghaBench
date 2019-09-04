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
struct feat_fd {int /*<<< orphan*/  fd; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ trace_report (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int process_tracing_data(struct feat_fd *ff, void *data)
{
	ssize_t ret = trace_report(ff->fd, data, false);

	return ret < 0 ? -1 : 0;
}