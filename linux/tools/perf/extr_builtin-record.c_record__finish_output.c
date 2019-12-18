#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  size; } ;
struct perf_data {TYPE_1__ file; scalar_t__ is_pipe; } ;
struct record {int /*<<< orphan*/  evlist; TYPE_3__* session; scalar_t__ buildid_all; int /*<<< orphan*/  no_buildid; scalar_t__ bytes_written; struct perf_data data; } ;
struct TYPE_6__ {int /*<<< orphan*/  data_size; } ;
struct TYPE_7__ {TYPE_2__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  dsos__hit_all (TYPE_3__*) ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int perf_data__fd (struct perf_data*) ; 
 int /*<<< orphan*/  perf_session__write_header (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  process_buildids (struct record*) ; 

__attribute__((used)) static void
record__finish_output(struct record *rec)
{
	struct perf_data *data = &rec->data;
	int fd = perf_data__fd(data);

	if (data->is_pipe)
		return;

	rec->session->header.data_size += rec->bytes_written;
	data->file.size = lseek(perf_data__fd(data), 0, SEEK_CUR);

	if (!rec->no_buildid) {
		process_buildids(rec);

		if (rec->buildid_all)
			dsos__hit_all(rec->session);
	}
	perf_session__write_header(rec->session, rec->evlist, fd, true);

	return;
}