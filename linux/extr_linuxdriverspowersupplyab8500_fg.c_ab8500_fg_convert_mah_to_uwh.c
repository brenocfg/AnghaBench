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
typedef  int u64 ;
typedef  int u32 ;
struct ab8500_fg {scalar_t__ vbat_nom; } ;

/* Variables and functions */
 int do_div (int,int) ; 

__attribute__((used)) static int ab8500_fg_convert_mah_to_uwh(struct ab8500_fg *di, int cap_mah)
{
	u64 div_res;
	u32 div_rem;

	div_res = ((u64) cap_mah) * ((u64) di->vbat_nom);
	div_rem = do_div(div_res, 1000);

	/* Make sure to round upwards if necessary */
	if (div_rem >= 1000 / 2)
		div_res++;

	return (int) div_res;
}