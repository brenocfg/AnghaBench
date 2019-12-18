#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ slave; } ;
struct TYPE_8__ {TYPE_1__ dama; } ;
typedef  TYPE_2__ ax25_dev ;

/* Variables and functions */
 int /*<<< orphan*/  ax25_check_dama_slave (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_ds_del_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_kiss_cmd (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

void ax25_dev_dama_off(ax25_dev *ax25_dev)
{
	if (ax25_dev == NULL)
		return;

	if (ax25_dev->dama.slave && !ax25_check_dama_slave(ax25_dev)) {
		ax25_kiss_cmd(ax25_dev, 5, 0);
		ax25_dev->dama.slave = 0;
		ax25_ds_del_timer(ax25_dev);
	}
}