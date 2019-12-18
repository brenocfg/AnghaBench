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
struct hists {int dummy; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __hists__init (struct hists*,int /*<<< orphan*/ *) ; 
 struct hists* evsel__hists (struct evsel*) ; 
 int /*<<< orphan*/  perf_hpp_list ; 

__attribute__((used)) static int hists_evsel__init(struct evsel *evsel)
{
	struct hists *hists = evsel__hists(evsel);

	__hists__init(hists, &perf_hpp_list);
	return 0;
}