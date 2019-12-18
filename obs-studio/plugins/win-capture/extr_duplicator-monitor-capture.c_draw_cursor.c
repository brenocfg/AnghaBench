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
struct duplicator_capture {int rot; int /*<<< orphan*/  width; int /*<<< orphan*/  height; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  cursor_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  cursor_draw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void draw_cursor(struct duplicator_capture *capture)
{
	cursor_draw(&capture->cursor_data, -capture->x, -capture->y, 1.0f, 1.0f,
		    capture->rot % 180 == 0 ? capture->width : capture->height,
		    capture->rot % 180 == 0 ? capture->height : capture->width);
}