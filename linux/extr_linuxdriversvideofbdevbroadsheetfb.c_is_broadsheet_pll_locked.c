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
struct broadsheetfb_par {int dummy; } ;

/* Variables and functions */
 int broadsheet_read_reg (struct broadsheetfb_par*,int) ; 

__attribute__((used)) static int is_broadsheet_pll_locked(struct broadsheetfb_par *par)
{
	return broadsheet_read_reg(par, 0x000A) & 0x0001;
}