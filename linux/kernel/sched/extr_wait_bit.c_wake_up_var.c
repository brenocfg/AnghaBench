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
 int /*<<< orphan*/  __var_waitqueue (void*) ; 
 int /*<<< orphan*/  __wake_up_bit (int /*<<< orphan*/ ,void*,int) ; 

void wake_up_var(void *var)
{
	__wake_up_bit(__var_waitqueue(var), var, -1);
}