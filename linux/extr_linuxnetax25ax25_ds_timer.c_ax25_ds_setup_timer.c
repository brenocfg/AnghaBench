#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  slave_timer; } ;
struct TYPE_5__ {TYPE_1__ dama; } ;
typedef  TYPE_2__ ax25_dev ;

/* Variables and functions */
 int /*<<< orphan*/  ax25_ds_timeout ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ax25_ds_setup_timer(ax25_dev *ax25_dev)
{
	timer_setup(&ax25_dev->dama.slave_timer, ax25_ds_timeout, 0);
}