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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  iis_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 TYPE_1__ s3c24xx_i2s ; 

u32 s3c24xx_i2s_get_clockrate(void)
{
	return clk_get_rate(s3c24xx_i2s.iis_clk);
}