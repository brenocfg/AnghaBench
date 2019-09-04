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

/* Variables and functions */
 unsigned long** shadow_plb ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

void init()
{
	int i;

	srand((unsigned int)time(NULL));

	for (i = 0; i < 4; i++) {
		shadow_plb[i][0] = 0;
		shadow_plb[i][1] = ~(unsigned long)0;
	}
}