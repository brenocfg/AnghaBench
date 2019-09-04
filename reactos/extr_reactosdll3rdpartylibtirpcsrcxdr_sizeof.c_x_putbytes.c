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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_3__ {int /*<<< orphan*/  x_handy; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static bool_t
x_putbytes(XDR *xdrs, const char *bp, u_int len)
{
	xdrs->x_handy += len;
	return (TRUE);
}