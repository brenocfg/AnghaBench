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
typedef  int u_int32_t ;

/* Variables and functions */
 int rand () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 

u_int32_t arc4random()
{
	static int did_srand = 0;
	u_int32_t ret;

	if (!did_srand) {
		srand(0);
		did_srand = 1;
	}

	ret = rand() << 10 ^ rand();
	return ret;
}