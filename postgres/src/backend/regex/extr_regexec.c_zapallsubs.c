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
struct TYPE_3__ {int rm_so; int rm_eo; } ;
typedef  TYPE_1__ regmatch_t ;

/* Variables and functions */

__attribute__((used)) static void
zapallsubs(regmatch_t *p,
		   size_t n)
{
	size_t		i;

	for (i = n - 1; i > 0; i--)
	{
		p[i].rm_so = -1;
		p[i].rm_eo = -1;
	}
}