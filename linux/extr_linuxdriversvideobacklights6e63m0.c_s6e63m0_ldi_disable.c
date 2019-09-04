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
struct s6e63m0 {int dummy; } ;

/* Variables and functions */
 int s6e63m0_panel_send_sequence (struct s6e63m0*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_stand_by_on ; 

__attribute__((used)) static int s6e63m0_ldi_disable(struct s6e63m0 *lcd)
{
	int ret;

	ret = s6e63m0_panel_send_sequence(lcd, seq_stand_by_on);

	return ret;
}