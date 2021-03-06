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
typedef  scalar_t__ int16 ;
typedef  int /*<<< orphan*/  FmgrInfo ;

/* Variables and functions */

__attribute__((used)) static bool
gbt_int2lt(const void *a, const void *b, FmgrInfo *flinfo)
{
	return (*((const int16 *) a) < *((const int16 *) b));
}