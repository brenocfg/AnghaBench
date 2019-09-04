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
struct lms501kf03 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int lms501kf03_panel_send_sequence (struct lms501kf03*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_display_on ; 

__attribute__((used)) static int lms501kf03_ldi_enable(struct lms501kf03 *lcd)
{
	return lms501kf03_panel_send_sequence(lcd, seq_display_on,
					ARRAY_SIZE(seq_display_on));
}