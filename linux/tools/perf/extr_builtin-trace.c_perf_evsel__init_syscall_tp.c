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
struct syscall_tp {int /*<<< orphan*/  id; } ;
struct evsel {struct syscall_tp* priv; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 struct syscall_tp* malloc (int) ; 
 scalar_t__ perf_evsel__init_tp_uint_field (struct evsel*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zfree (struct syscall_tp**) ; 

__attribute__((used)) static int perf_evsel__init_syscall_tp(struct evsel *evsel)
{
	struct syscall_tp *sc = evsel->priv = malloc(sizeof(struct syscall_tp));

	if (evsel->priv != NULL) {
		if (perf_evsel__init_tp_uint_field(evsel, &sc->id, "__syscall_nr") &&
		    perf_evsel__init_tp_uint_field(evsel, &sc->id, "nr"))
			goto out_delete;
		return 0;
	}

	return -ENOMEM;
out_delete:
	zfree(&evsel->priv);
	return -ENOENT;
}