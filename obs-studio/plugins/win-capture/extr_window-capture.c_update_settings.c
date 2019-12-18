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
struct window_capture {int priority; void* compatibility; void* use_wildcards; void* cursor; int /*<<< orphan*/ * class; int /*<<< orphan*/ * executable; int /*<<< orphan*/  source; int /*<<< orphan*/ * title; } ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  enum window_priority { ____Placeholder_window_priority } window_priority ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  build_window_strings (char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 void* obs_data_get_bool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_source_get_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_settings(struct window_capture *wc, obs_data_t *s)
{
	const char *window = obs_data_get_string(s, "window");
	int priority = (int)obs_data_get_int(s, "priority");

	bfree(wc->title);
	bfree(wc->class);
	bfree(wc->executable);

	build_window_strings(window, &wc->class, &wc->title, &wc->executable);

	if (wc->title != NULL) {
		blog(LOG_INFO,
		     "[window-capture: '%s'] update settings:\n"
		     "\texecutable: %s",
		     obs_source_get_name(wc->source), wc->executable);
		blog(LOG_DEBUG, "\tclass:      %s", wc->class);
	}

	wc->priority = (enum window_priority)priority;
	wc->cursor = obs_data_get_bool(s, "cursor");
	wc->use_wildcards = obs_data_get_bool(s, "use_wildcards");
	wc->compatibility = obs_data_get_bool(s, "compatibility");
}