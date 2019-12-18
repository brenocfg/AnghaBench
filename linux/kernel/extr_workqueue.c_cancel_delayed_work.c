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
struct delayed_work {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int __cancel_work (int /*<<< orphan*/ *,int) ; 

bool cancel_delayed_work(struct delayed_work *dwork)
{
	return __cancel_work(&dwork->work, true);
}