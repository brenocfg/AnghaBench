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
struct game_capture {int /*<<< orphan*/  config; int /*<<< orphan*/  executable; int /*<<< orphan*/  class; int /*<<< orphan*/  title; int /*<<< orphan*/  cursor_data; scalar_t__ hotkey_pair; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct game_capture*) ; 
 int /*<<< orphan*/  cursor_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_config (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_hotkey_pair_unregister (scalar_t__) ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 int /*<<< orphan*/  stop_capture (struct game_capture*) ; 

__attribute__((used)) static void game_capture_destroy(void *data)
{
	struct game_capture *gc = data;
	stop_capture(gc);

	if (gc->hotkey_pair)
		obs_hotkey_pair_unregister(gc->hotkey_pair);

	obs_enter_graphics();
	cursor_data_free(&gc->cursor_data);
	obs_leave_graphics();

	dstr_free(&gc->title);
	dstr_free(&gc->class);
	dstr_free(&gc->executable);
	free_config(&gc->config);
	bfree(gc);
}