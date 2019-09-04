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
typedef  int u32 ;
struct hdspm {int settings_register; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDSPM_WR_SETTINGS ; 
 int /*<<< orphan*/  hdspm_write (struct hdspm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hdspm_set_tristate(struct hdspm *hdspm, int mode, u32 regmask)
{
	hdspm->settings_register &= ~(regmask * 3);
	hdspm->settings_register |= (regmask * mode);
	hdspm_write(hdspm, HDSPM_WR_SETTINGS, hdspm->settings_register);

	return 0;
}