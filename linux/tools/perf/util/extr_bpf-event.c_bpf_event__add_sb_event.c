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
struct perf_event_attr {int sample_id_all; int watermark; int bpf_event; int size; int wakeup_watermark; int /*<<< orphan*/  config; int /*<<< orphan*/  type; } ;
struct perf_env {int dummy; } ;
struct evlist {int dummy; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_COUNT_SW_DUMMY ; 
 int /*<<< orphan*/  PERF_TYPE_SOFTWARE ; 
 int /*<<< orphan*/  bpf_event__sb_cb ; 
 int perf_evlist__add_sb_event (struct evlist**,struct perf_event_attr*,int /*<<< orphan*/ ,struct perf_env*) ; 

int bpf_event__add_sb_event(struct evlist **evlist,
			    struct perf_env *env)
{
	struct perf_event_attr attr = {
		.type	          = PERF_TYPE_SOFTWARE,
		.config           = PERF_COUNT_SW_DUMMY,
		.sample_id_all    = 1,
		.watermark        = 1,
		.bpf_event        = 1,
		.size	   = sizeof(attr), /* to capture ABI version */
	};

	/*
	 * Older gcc versions don't support designated initializers, like above,
	 * for unnamed union members, such as the following:
	 */
	attr.wakeup_watermark = 1;

	return perf_evlist__add_sb_event(evlist, &attr, bpf_event__sb_cb, env);
}