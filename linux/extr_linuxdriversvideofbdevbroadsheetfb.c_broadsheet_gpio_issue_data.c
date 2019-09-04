#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct broadsheetfb_par {TYPE_1__* board; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_ctl ) (struct broadsheetfb_par*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* set_hdb ) (struct broadsheetfb_par*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BS_WR ; 
 int /*<<< orphan*/  stub1 (struct broadsheetfb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct broadsheetfb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct broadsheetfb_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void broadsheet_gpio_issue_data(struct broadsheetfb_par *par, u16 data)
{
	par->board->set_ctl(par, BS_WR, 0);
	par->board->set_hdb(par, data);
	par->board->set_ctl(par, BS_WR, 1);
}