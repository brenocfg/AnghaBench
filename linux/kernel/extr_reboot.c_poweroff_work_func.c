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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __orderly_poweroff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poweroff_force ; 

__attribute__((used)) static void poweroff_work_func(struct work_struct *work)
{
	__orderly_poweroff(poweroff_force);
}