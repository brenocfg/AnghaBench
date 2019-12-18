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
struct maps {int dummy; } ;
struct TYPE_2__ {struct maps maps; } ;
struct machine {TYPE_1__ kmaps; } ;

/* Variables and functions */

__attribute__((used)) static inline
struct maps *machine__kernel_maps(struct machine *machine)
{
	return &machine->kmaps.maps;
}