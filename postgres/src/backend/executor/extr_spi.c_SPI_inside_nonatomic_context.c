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
struct TYPE_2__ {scalar_t__ atomic; } ;

/* Variables and functions */
 TYPE_1__* _SPI_current ; 

bool
SPI_inside_nonatomic_context(void)
{
	if (_SPI_current == NULL)
		return false;			/* not in any SPI context at all */
	if (_SPI_current->atomic)
		return false;			/* it's atomic (ie function not procedure) */
	return true;
}