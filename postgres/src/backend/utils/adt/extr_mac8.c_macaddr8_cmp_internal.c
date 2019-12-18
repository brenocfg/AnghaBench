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
typedef  int /*<<< orphan*/  macaddr8 ;
typedef  int int32 ;

/* Variables and functions */
 scalar_t__ hibits (int /*<<< orphan*/ *) ; 
 scalar_t__ lobits (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32
macaddr8_cmp_internal(macaddr8 *a1, macaddr8 *a2)
{
	if (hibits(a1) < hibits(a2))
		return -1;
	else if (hibits(a1) > hibits(a2))
		return 1;
	else if (lobits(a1) < lobits(a2))
		return -1;
	else if (lobits(a1) > lobits(a2))
		return 1;
	else
		return 0;
}