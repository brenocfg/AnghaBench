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
struct perf_evsel {int dummy; } ;
struct hists {int dummy; } ;
struct hists_evsel {struct hists hists; } ;

/* Variables and functions */

__attribute__((used)) static inline struct hists *evsel__hists(struct perf_evsel *evsel)
{
	struct hists_evsel *hevsel = (struct hists_evsel *)evsel;
	return &hevsel->hists;
}