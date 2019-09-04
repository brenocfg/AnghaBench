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
struct rcar_sysc_ch {int dummy; } ;

/* Variables and functions */
 int rcar_sysc_power (struct rcar_sysc_ch const*,int) ; 

__attribute__((used)) static int rcar_sysc_power_down(const struct rcar_sysc_ch *sysc_ch)
{
	return rcar_sysc_power(sysc_ch, false);
}