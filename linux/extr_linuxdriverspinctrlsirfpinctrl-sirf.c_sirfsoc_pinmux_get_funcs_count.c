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
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 int sirfsoc_pmxfunc_cnt ; 

__attribute__((used)) static int sirfsoc_pinmux_get_funcs_count(struct pinctrl_dev *pmxdev)
{
	return sirfsoc_pmxfunc_cnt;
}