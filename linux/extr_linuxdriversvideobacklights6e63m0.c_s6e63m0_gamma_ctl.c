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
struct s6e63m0 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * gamma_22_table; } ;

/* Variables and functions */
 int _s6e63m0_gamma_ctl (struct s6e63m0*,int /*<<< orphan*/ ) ; 
 TYPE_1__ gamma_table ; 

__attribute__((used)) static int s6e63m0_gamma_ctl(struct s6e63m0 *lcd, int gamma)
{
	int ret = 0;

	ret = _s6e63m0_gamma_ctl(lcd, gamma_table.gamma_22_table[gamma]);

	return ret;
}