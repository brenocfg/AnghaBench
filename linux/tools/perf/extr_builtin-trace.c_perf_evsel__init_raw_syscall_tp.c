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
struct syscall_tp {int dummy; } ;
struct evsel {int /*<<< orphan*/ * priv; void* handler; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  id ; 
 int /*<<< orphan*/ * malloc (int) ; 
 scalar_t__ perf_evsel__init_sc_tp_uint_field (struct evsel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ **) ; 

__attribute__((used)) static int perf_evsel__init_raw_syscall_tp(struct evsel *evsel, void *handler)
{
	evsel->priv = malloc(sizeof(struct syscall_tp));
	if (evsel->priv != NULL) {
		if (perf_evsel__init_sc_tp_uint_field(evsel, id))
			goto out_delete;

		evsel->handler = handler;
		return 0;
	}

	return -ENOMEM;

out_delete:
	zfree(&evsel->priv);
	return -ENOENT;
}