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
struct TYPE_2__ {scalar_t__ nr_cblocks; } ;
struct record {int no_buildid_cache; int no_buildid; TYPE_1__ opts; } ;

/* Variables and functions */
 scalar_t__ nr_cblocks_default ; 
 int perf_default_config (char const*,char const*,void*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_record_config(const char *var, const char *value, void *cb)
{
	struct record *rec = cb;

	if (!strcmp(var, "record.build-id")) {
		if (!strcmp(value, "cache"))
			rec->no_buildid_cache = false;
		else if (!strcmp(value, "no-cache"))
			rec->no_buildid_cache = true;
		else if (!strcmp(value, "skip"))
			rec->no_buildid = true;
		else
			return -1;
		return 0;
	}
	if (!strcmp(var, "record.call-graph")) {
		var = "call-graph.record-mode";
		return perf_default_config(var, value, cb);
	}
#ifdef HAVE_AIO_SUPPORT
	if (!strcmp(var, "record.aio")) {
		rec->opts.nr_cblocks = strtol(value, NULL, 0);
		if (!rec->opts.nr_cblocks)
			rec->opts.nr_cblocks = nr_cblocks_default;
	}
#endif

	return 0;
}