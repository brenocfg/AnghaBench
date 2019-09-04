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
struct perf_header {int dummy; } ;
struct perf_session {int /*<<< orphan*/  repipe; int /*<<< orphan*/  data; struct perf_header header; } ;
struct perf_pipe_file_header {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  perf_data__fd (int /*<<< orphan*/ ) ; 
 scalar_t__ perf_file_header__read_pipe (struct perf_pipe_file_header*,struct perf_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int perf_header__read_pipe(struct perf_session *session)
{
	struct perf_header *header = &session->header;
	struct perf_pipe_file_header f_header;

	if (perf_file_header__read_pipe(&f_header, header,
					perf_data__fd(session->data),
					session->repipe) < 0) {
		pr_debug("incompatible file format\n");
		return -EINVAL;
	}

	return 0;
}