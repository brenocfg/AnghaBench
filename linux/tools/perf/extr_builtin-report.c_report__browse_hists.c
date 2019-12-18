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
struct report {int /*<<< orphan*/  annotation_opts; int /*<<< orphan*/  min_percent; struct perf_session* session; } ;
struct TYPE_2__ {int /*<<< orphan*/  env; } ;
struct perf_session {TYPE_1__ header; struct evlist* evlist; } ;
struct evlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOCDIR ; 
 int K_SWITCH_INPUT_DATA ; 
 int /*<<< orphan*/  TIPDIR ; 
 int perf_evlist__tty_browse_hists (struct evlist*,struct report*,char const*) ; 
 int perf_evlist__tui_browse_hists (struct evlist*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 char* perf_tip (int /*<<< orphan*/ ) ; 
 int report__gtk_browse_hists (struct report*,char const*) ; 
 int /*<<< orphan*/  system_path (int /*<<< orphan*/ ) ; 
 int use_browser ; 

__attribute__((used)) static int report__browse_hists(struct report *rep)
{
	int ret;
	struct perf_session *session = rep->session;
	struct evlist *evlist = session->evlist;
	const char *help = perf_tip(system_path(TIPDIR));

	if (help == NULL) {
		/* fallback for people who don't install perf ;-) */
		help = perf_tip(DOCDIR);
		if (help == NULL)
			help = "Cannot load tips.txt file, please install perf!";
	}

	switch (use_browser) {
	case 1:
		ret = perf_evlist__tui_browse_hists(evlist, help, NULL,
						    rep->min_percent,
						    &session->header.env,
						    true, &rep->annotation_opts);
		/*
		 * Usually "ret" is the last pressed key, and we only
		 * care if the key notifies us to switch data file.
		 */
		if (ret != K_SWITCH_INPUT_DATA)
			ret = 0;
		break;
	case 2:
		ret = report__gtk_browse_hists(rep, help);
		break;
	default:
		ret = perf_evlist__tty_browse_hists(evlist, rep, help);
		break;
	}

	return ret;
}