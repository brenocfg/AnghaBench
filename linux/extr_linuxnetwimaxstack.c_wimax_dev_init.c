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
struct wimax_dev {int /*<<< orphan*/  mutex_reset; int /*<<< orphan*/  mutex; int /*<<< orphan*/  id_table_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __WIMAX_ST_NULL ; 
 int /*<<< orphan*/  __wimax_state_set (struct wimax_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void wimax_dev_init(struct wimax_dev *wimax_dev)
{
	INIT_LIST_HEAD(&wimax_dev->id_table_node);
	__wimax_state_set(wimax_dev, __WIMAX_ST_NULL);
	mutex_init(&wimax_dev->mutex);
	mutex_init(&wimax_dev->mutex_reset);
}