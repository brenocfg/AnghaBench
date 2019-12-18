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
 int /*<<< orphan*/  protect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_led (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ignore_me(int signum)
{
	protect(0);
	set_led(0);
}