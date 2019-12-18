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
struct evsel_runtime {int dummy; } ;
struct evsel {struct evsel_runtime* priv; } ;

/* Variables and functions */
 struct evsel_runtime* zalloc (int) ; 

__attribute__((used)) static struct evsel_runtime *perf_evsel__get_runtime(struct evsel *evsel)
{
	struct evsel_runtime *r = evsel->priv;

	if (r == NULL) {
		r = zalloc(sizeof(struct evsel_runtime));
		evsel->priv = r;
	}

	return r;
}