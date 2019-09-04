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
typedef  unsigned long u_long ;

/* Variables and functions */
 scalar_t__ PHP_RAND_MAX ; 

__attribute__((used)) static int
do_rand(unsigned long *ctx)
{
	return ((*ctx = *ctx * 1103515245 + 12345) % ((u_long)PHP_RAND_MAX + 1));
}