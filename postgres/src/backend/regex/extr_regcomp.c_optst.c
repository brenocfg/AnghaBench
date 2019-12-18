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
struct vars {int dummy; } ;
struct subre {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
optst(struct vars *v,
	  struct subre *t)
{
	/*
	 * DGP (2007-11-13): I assume it was the programmer's intent to eventually
	 * come back and add code to optimize subRE trees, but the routine coded
	 * just spends effort traversing the tree and doing nothing. We can do
	 * nothing with less effort.
	 */
	return;
}