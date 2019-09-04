#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_3__ {int /*<<< orphan*/  x_handy; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 scalar_t__ BYTES_PER_XDR_UNIT ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static bool_t
x_putlong(XDR *xdrs, const long *longp)
{
	xdrs->x_handy += BYTES_PER_XDR_UNIT;
	return (TRUE);
}