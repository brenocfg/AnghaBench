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
struct TYPE_3__ {scalar_t__ t2; int /*<<< orphan*/  t2timer; } ;
typedef  TYPE_1__ ax25_cb ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

void ax25_start_t2timer(ax25_cb *ax25)
{
	mod_timer(&ax25->t2timer, jiffies + ax25->t2);
}