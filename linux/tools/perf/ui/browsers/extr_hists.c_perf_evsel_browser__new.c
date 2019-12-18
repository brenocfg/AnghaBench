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
struct perf_env {int dummy; } ;
struct hist_browser_timer {int dummy; } ;
struct hist_browser {struct annotation_options* annotation_opts; int /*<<< orphan*/  title; struct perf_env* env; struct hist_browser_timer* hbt; } ;
struct evsel {int dummy; } ;
struct annotation_options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  evsel__hists (struct evsel*) ; 
 struct hist_browser* hist_browser__new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hists_browser__scnprintf_title ; 

__attribute__((used)) static struct hist_browser *
perf_evsel_browser__new(struct evsel *evsel,
			struct hist_browser_timer *hbt,
			struct perf_env *env,
			struct annotation_options *annotation_opts)
{
	struct hist_browser *browser = hist_browser__new(evsel__hists(evsel));

	if (browser) {
		browser->hbt   = hbt;
		browser->env   = env;
		browser->title = hists_browser__scnprintf_title;
		browser->annotation_opts = annotation_opts;
	}
	return browser;
}