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
struct duplicator_capture {float reset_timeout; scalar_t__ rot; scalar_t__ y; scalar_t__ x; scalar_t__ height; scalar_t__ width; int /*<<< orphan*/ * duplicator; int /*<<< orphan*/  cursor_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  cursor_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_duplicator_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_capture_data(struct duplicator_capture *capture)
{
	gs_duplicator_destroy(capture->duplicator);
	cursor_data_free(&capture->cursor_data);
	capture->duplicator = NULL;
	capture->width = 0;
	capture->height = 0;
	capture->x = 0;
	capture->y = 0;
	capture->rot = 0;
	capture->reset_timeout = 0.0f;
}