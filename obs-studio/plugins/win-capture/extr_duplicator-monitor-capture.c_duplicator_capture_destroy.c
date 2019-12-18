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
struct duplicator_capture {int /*<<< orphan*/  cursor_data; int /*<<< orphan*/  duplicator; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct duplicator_capture*) ; 
 int /*<<< orphan*/  cursor_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_duplicator_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 

__attribute__((used)) static void duplicator_capture_destroy(void *data)
{
	struct duplicator_capture *capture = data;

	obs_enter_graphics();

	gs_duplicator_destroy(capture->duplicator);
	cursor_data_free(&capture->cursor_data);

	obs_leave_graphics();

	bfree(capture);
}