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
struct TYPE_2__ {int /*<<< orphan*/  env; } ;
struct perf_session {TYPE_1__ header; } ;
struct perf_mem {scalar_t__ phys_addr; int /*<<< orphan*/  cpu_bitmap; int /*<<< orphan*/  cpu_list; int /*<<< orphan*/  tool; int /*<<< orphan*/  force; } ;
struct perf_data {int /*<<< orphan*/  force; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct perf_session*) ; 
 int /*<<< orphan*/  PERF_DATA_MODE_READ ; 
 int PTR_ERR (struct perf_session*) ; 
 int /*<<< orphan*/  input_name ; 
 int perf_session__cpu_bitmap (struct perf_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_session__delete (struct perf_session*) ; 
 struct perf_session* perf_session__new (struct perf_data*,int,int /*<<< orphan*/ *) ; 
 int perf_session__process_events (struct perf_session*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int symbol__init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int report_raw_events(struct perf_mem *mem)
{
	struct perf_data data = {
		.path  = input_name,
		.mode  = PERF_DATA_MODE_READ,
		.force = mem->force,
	};
	int ret;
	struct perf_session *session = perf_session__new(&data, false,
							 &mem->tool);

	if (IS_ERR(session))
		return PTR_ERR(session);

	if (mem->cpu_list) {
		ret = perf_session__cpu_bitmap(session, mem->cpu_list,
					       mem->cpu_bitmap);
		if (ret < 0)
			goto out_delete;
	}

	ret = symbol__init(&session->header.env);
	if (ret < 0)
		goto out_delete;

	if (mem->phys_addr)
		printf("# PID, TID, IP, ADDR, PHYS ADDR, LOCAL WEIGHT, DSRC, SYMBOL\n");
	else
		printf("# PID, TID, IP, ADDR, LOCAL WEIGHT, DSRC, SYMBOL\n");

	ret = perf_session__process_events(session);

out_delete:
	perf_session__delete(session);
	return ret;
}