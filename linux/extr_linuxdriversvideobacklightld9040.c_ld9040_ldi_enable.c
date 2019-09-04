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
struct ld9040 {int dummy; } ;

/* Variables and functions */
 int ld9040_panel_send_sequence (struct ld9040*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_display_on ; 

__attribute__((used)) static int ld9040_ldi_enable(struct ld9040 *lcd)
{
	return ld9040_panel_send_sequence(lcd, seq_display_on);
}