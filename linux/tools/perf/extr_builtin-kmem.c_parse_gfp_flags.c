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
struct trace_seq {int /*<<< orphan*/ * buffer; } ;
struct tep_record {int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  cpu; } ;
struct perf_sample {int /*<<< orphan*/  raw_size; int /*<<< orphan*/  raw_data; int /*<<< orphan*/  cpu; } ;
struct gfp_flag {unsigned int flags; int /*<<< orphan*/  compact_str; int /*<<< orphan*/  human_readable; } ;
struct evsel {TYPE_1__* tp_format; } ;
struct TYPE_2__ {int /*<<< orphan*/  tep; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  TEP_PRINT_INFO ; 
 scalar_t__ bsearch (struct gfp_flag*,struct gfp_flag*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compact_gfp_flags (char*) ; 
 int /*<<< orphan*/  gfpcmp ; 
 struct gfp_flag* gfps ; 
 int nr_gfps ; 
 int /*<<< orphan*/  qsort (struct gfp_flag*,int,int,int /*<<< orphan*/ ) ; 
 struct gfp_flag* realloc (struct gfp_flag*,int) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char* strtok_r (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  tep_print_event (int /*<<< orphan*/ ,struct trace_seq*,struct tep_record*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_destroy (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_init (struct trace_seq*) ; 

__attribute__((used)) static int parse_gfp_flags(struct evsel *evsel, struct perf_sample *sample,
			   unsigned int gfp_flags)
{
	struct tep_record record = {
		.cpu = sample->cpu,
		.data = sample->raw_data,
		.size = sample->raw_size,
	};
	struct trace_seq seq;
	char *str, *pos = NULL;

	if (nr_gfps) {
		struct gfp_flag key = {
			.flags = gfp_flags,
		};

		if (bsearch(&key, gfps, nr_gfps, sizeof(*gfps), gfpcmp))
			return 0;
	}

	trace_seq_init(&seq);
	tep_print_event(evsel->tp_format->tep,
			&seq, &record, "%s", TEP_PRINT_INFO);

	str = strtok_r(seq.buffer, " ", &pos);
	while (str) {
		if (!strncmp(str, "gfp_flags=", 10)) {
			struct gfp_flag *new;

			new = realloc(gfps, (nr_gfps + 1) * sizeof(*gfps));
			if (new == NULL)
				return -ENOMEM;

			gfps = new;
			new += nr_gfps++;

			new->flags = gfp_flags;
			new->human_readable = strdup(str + 10);
			new->compact_str = compact_gfp_flags(str + 10);
			if (!new->human_readable || !new->compact_str)
				return -ENOMEM;

			qsort(gfps, nr_gfps, sizeof(*gfps), gfpcmp);
		}

		str = strtok_r(NULL, " ", &pos);
	}

	trace_seq_destroy(&seq);
	return 0;
}