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
struct hdspm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDSPM_ClockModeMaster ; 
 int /*<<< orphan*/  HDSPM_c0Master ; 
 scalar_t__ hdspm_is_raydat_or_aio (struct hdspm*) ; 
 int /*<<< orphan*/  hdspm_set_toggle_setting (struct hdspm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hdspm_set_system_clock_mode(struct hdspm *hdspm, int mode)
{
	hdspm_set_toggle_setting(hdspm,
			(hdspm_is_raydat_or_aio(hdspm)) ?
			HDSPM_c0Master : HDSPM_ClockModeMaster,
			(0 == mode));
}