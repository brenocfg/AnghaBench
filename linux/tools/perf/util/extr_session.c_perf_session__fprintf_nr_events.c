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
struct perf_session {TYPE_1__* evlist; int /*<<< orphan*/  header; } ;
struct TYPE_2__ {int /*<<< orphan*/  stats; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  HEADER_AUXTRACE ; 
 scalar_t__ events_stats__fprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ perf_header__has_feat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

size_t perf_session__fprintf_nr_events(struct perf_session *session, FILE *fp)
{
	size_t ret;
	const char *msg = "";

	if (perf_header__has_feat(&session->header, HEADER_AUXTRACE))
		msg = " (excludes AUX area (e.g. instruction trace) decoded / synthesized events)";

	ret = fprintf(fp, "\nAggregated stats:%s\n", msg);

	ret += events_stats__fprintf(&session->evlist->stats, fp);
	return ret;
}