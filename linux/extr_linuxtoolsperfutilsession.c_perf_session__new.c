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
struct perf_tool {int ordered_events; scalar_t__ ordering_requires_timestamps; } ;
struct TYPE_3__ {int /*<<< orphan*/ * env; int /*<<< orphan*/  single_address_space; } ;
struct TYPE_4__ {TYPE_1__ host; } ;
struct perf_session {int repipe; int /*<<< orphan*/  evlist; TYPE_2__ machines; struct perf_data* data; int /*<<< orphan*/  ordered_events; int /*<<< orphan*/  auxtrace_index; struct perf_tool* tool; } ;
struct perf_data {int /*<<< orphan*/  is_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_printf (char*) ; 
 int /*<<< orphan*/  machines__init (TYPE_2__*) ; 
 int /*<<< orphan*/  ordered_events__deliver_event ; 
 int /*<<< orphan*/  ordered_events__init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_data__close (struct perf_data*) ; 
 scalar_t__ perf_data__is_read (struct perf_data*) ; 
 scalar_t__ perf_data__is_write (struct perf_data*) ; 
 scalar_t__ perf_data__open (struct perf_data*) ; 
 int /*<<< orphan*/  perf_env ; 
 int /*<<< orphan*/  perf_env__single_address_space (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_evlist__sample_id_all (int /*<<< orphan*/ ) ; 
 scalar_t__ perf_session__create_kernel_maps (struct perf_session*) ; 
 int /*<<< orphan*/  perf_session__delete (struct perf_session*) ; 
 scalar_t__ perf_session__open (struct perf_session*) ; 
 int /*<<< orphan*/  perf_session__set_comm_exec (struct perf_session*) ; 
 int /*<<< orphan*/  perf_session__set_id_hdr_size (struct perf_session*) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 struct perf_session* zalloc (int) ; 

struct perf_session *perf_session__new(struct perf_data *data,
				       bool repipe, struct perf_tool *tool)
{
	struct perf_session *session = zalloc(sizeof(*session));

	if (!session)
		goto out;

	session->repipe = repipe;
	session->tool   = tool;
	INIT_LIST_HEAD(&session->auxtrace_index);
	machines__init(&session->machines);
	ordered_events__init(&session->ordered_events, ordered_events__deliver_event);

	if (data) {
		if (perf_data__open(data))
			goto out_delete;

		session->data = data;

		if (perf_data__is_read(data)) {
			if (perf_session__open(session) < 0)
				goto out_close;

			/*
			 * set session attributes that are present in perf.data
			 * but not in pipe-mode.
			 */
			if (!data->is_pipe) {
				perf_session__set_id_hdr_size(session);
				perf_session__set_comm_exec(session);
			}
		}
	} else  {
		session->machines.host.env = &perf_env;
	}

	session->machines.host.single_address_space =
		perf_env__single_address_space(session->machines.host.env);

	if (!data || perf_data__is_write(data)) {
		/*
		 * In O_RDONLY mode this will be performed when reading the
		 * kernel MMAP event, in perf_event__process_mmap().
		 */
		if (perf_session__create_kernel_maps(session) < 0)
			pr_warning("Cannot read kernel map\n");
	}

	/*
	 * In pipe-mode, evlist is empty until PERF_RECORD_HEADER_ATTR is
	 * processed, so perf_evlist__sample_id_all is not meaningful here.
	 */
	if ((!data || !data->is_pipe) && tool && tool->ordering_requires_timestamps &&
	    tool->ordered_events && !perf_evlist__sample_id_all(session->evlist)) {
		dump_printf("WARNING: No sample_id_all support, falling back to unordered processing\n");
		tool->ordered_events = false;
	}

	return session;

 out_close:
	perf_data__close(data);
 out_delete:
	perf_session__delete(session);
 out:
	return NULL;
}