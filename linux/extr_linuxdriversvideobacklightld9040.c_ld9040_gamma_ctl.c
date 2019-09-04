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
struct ld9040 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * gamma_22_table; } ;

/* Variables and functions */
 int _ld9040_gamma_ctl (struct ld9040*,int /*<<< orphan*/ ) ; 
 TYPE_1__ gamma_table ; 

__attribute__((used)) static int ld9040_gamma_ctl(struct ld9040 *lcd, int gamma)
{
	return _ld9040_gamma_ctl(lcd, gamma_table.gamma_22_table[gamma]);
}