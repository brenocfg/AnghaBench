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
struct game_capture_config {scalar_t__ scale_cx; scalar_t__ scale_cy; scalar_t__ mode; int /*<<< orphan*/  priority; int /*<<< orphan*/  executable; int /*<<< orphan*/  class; int /*<<< orphan*/  title; int /*<<< orphan*/  hook_rate; scalar_t__ force_scaling; } ;
struct game_capture {int error_acquiring; int activate_hook; int retry_interval; int wait_for_target_startup; int initial_config; struct game_capture_config config; int /*<<< orphan*/  priority; int /*<<< orphan*/  executable; int /*<<< orphan*/  class; int /*<<< orphan*/  title; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 scalar_t__ CAPTURE_MODE_HOTKEY ; 
 scalar_t__ CAPTURE_MODE_WINDOW ; 
 int DEFAULT_RETRY_INTERVAL ; 
 int /*<<< orphan*/  SETTING_CAPTURE_WINDOW ; 
 int capture_needs_reset (struct game_capture_config*,struct game_capture_config*) ; 
 int /*<<< orphan*/  dstr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_config (struct game_capture_config*) ; 
 int /*<<< orphan*/  get_config (struct game_capture_config*,int /*<<< orphan*/ *,char const*) ; 
 int hook_rate_to_float (int /*<<< orphan*/ ) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_capture (struct game_capture*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void game_capture_update(void *data, obs_data_t *settings)
{
	struct game_capture *gc = data;
	struct game_capture_config cfg;
	bool reset_capture = false;
	const char *window =
		obs_data_get_string(settings, SETTING_CAPTURE_WINDOW);

	get_config(&cfg, settings, window);
	reset_capture = capture_needs_reset(&cfg, &gc->config);

	if (cfg.force_scaling && (cfg.scale_cx == 0 || cfg.scale_cy == 0)) {
		gc->error_acquiring = true;
		warn("error acquiring, scale is bad");
	} else {
		gc->error_acquiring = false;
	}

	if (cfg.mode == CAPTURE_MODE_HOTKEY &&
	    gc->config.mode != CAPTURE_MODE_HOTKEY) {
		gc->activate_hook = false;
	} else {
		gc->activate_hook = !!window && !!*window;
	}

	free_config(&gc->config);
	gc->config = cfg;
	gc->retry_interval = DEFAULT_RETRY_INTERVAL *
			     hook_rate_to_float(gc->config.hook_rate);
	gc->wait_for_target_startup = false;

	dstr_free(&gc->title);
	dstr_free(&gc->class);
	dstr_free(&gc->executable);

	if (cfg.mode == CAPTURE_MODE_WINDOW) {
		dstr_copy(&gc->title, gc->config.title);
		dstr_copy(&gc->class, gc->config.class);
		dstr_copy(&gc->executable, gc->config.executable);
		gc->priority = gc->config.priority;
	}

	if (!gc->initial_config) {
		if (reset_capture) {
			stop_capture(gc);
		}
	} else {
		gc->initial_config = false;
	}
}