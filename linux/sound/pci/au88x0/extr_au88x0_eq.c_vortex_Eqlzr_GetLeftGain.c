#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t* this130; scalar_t__ this28; } ;
struct TYPE_4__ {TYPE_2__ eq; } ;
typedef  TYPE_1__ vortex_t ;
typedef  size_t u16 ;
typedef  TYPE_2__ eqlzr_t ;

/* Variables and functions */

__attribute__((used)) static int vortex_Eqlzr_GetLeftGain(vortex_t * vortex, u16 index, u16 * gain)
{
	eqlzr_t *eq = &(vortex->eq);

	if (eq->this28) {
		*gain = eq->this130[index];
		return 0;
	}
	return 1;
}