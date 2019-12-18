#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t size; scalar_t__ type; } ;
union perf_event {TYPE_2__ header; } ;
struct TYPE_3__ {scalar_t__ needs_swap; } ;
struct perf_session {scalar_t__ one_mmap_offset; int /*<<< orphan*/  evlist; TYPE_1__ header; int /*<<< orphan*/  data; union perf_event* one_mmap_addr; scalar_t__ one_mmap; } ;
struct perf_sample {int dummy; } ;
struct perf_event_header {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 scalar_t__ PERF_RECORD_USER_TYPE_START ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  event_swap (union perf_event*,int /*<<< orphan*/ ) ; 
 scalar_t__ lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int perf_data__fd (int /*<<< orphan*/ ) ; 
 scalar_t__ perf_data__is_pipe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_header__bswap (TYPE_2__*) ; 
 scalar_t__ perf_evlist__parse_sample (int /*<<< orphan*/ ,union perf_event*,struct perf_sample*) ; 
 int /*<<< orphan*/  perf_evlist__sample_id_all (int /*<<< orphan*/ ) ; 
 scalar_t__ readn (int,void*,size_t) ; 

int perf_session__peek_event(struct perf_session *session, off_t file_offset,
			     void *buf, size_t buf_sz,
			     union perf_event **event_ptr,
			     struct perf_sample *sample)
{
	union perf_event *event;
	size_t hdr_sz, rest;
	int fd;

	if (session->one_mmap && !session->header.needs_swap) {
		event = file_offset - session->one_mmap_offset +
			session->one_mmap_addr;
		goto out_parse_sample;
	}

	if (perf_data__is_pipe(session->data))
		return -1;

	fd = perf_data__fd(session->data);
	hdr_sz = sizeof(struct perf_event_header);

	if (buf_sz < hdr_sz)
		return -1;

	if (lseek(fd, file_offset, SEEK_SET) == (off_t)-1 ||
	    readn(fd, buf, hdr_sz) != (ssize_t)hdr_sz)
		return -1;

	event = (union perf_event *)buf;

	if (session->header.needs_swap)
		perf_event_header__bswap(&event->header);

	if (event->header.size < hdr_sz || event->header.size > buf_sz)
		return -1;

	rest = event->header.size - hdr_sz;

	if (readn(fd, buf, rest) != (ssize_t)rest)
		return -1;

	if (session->header.needs_swap)
		event_swap(event, perf_evlist__sample_id_all(session->evlist));

out_parse_sample:

	if (sample && event->header.type < PERF_RECORD_USER_TYPE_START &&
	    perf_evlist__parse_sample(session->evlist, event, sample))
		return -1;

	*event_ptr = event;

	return 0;
}