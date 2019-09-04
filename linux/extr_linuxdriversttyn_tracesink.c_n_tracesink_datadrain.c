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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* write ) (TYPE_2__*,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* this_tty ; 
 int /*<<< orphan*/  writelock ; 

void n_tracesink_datadrain(u8 *buf, int count)
{
	mutex_lock(&writelock);

	if ((buf != NULL) && (count > 0) && (this_tty != NULL))
		this_tty->ops->write(this_tty, buf, count);

	mutex_unlock(&writelock);
}