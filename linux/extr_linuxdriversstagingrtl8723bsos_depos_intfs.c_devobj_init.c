#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct dvobj_priv {int* macid; int processing_dev_remove; TYPE_1__ cam_ctl; int /*<<< orphan*/  disable_func; int /*<<< orphan*/  lock; int /*<<< orphan*/  setbw_mutex; int /*<<< orphan*/  setch_mutex; int /*<<< orphan*/  h2c_fwcmd_mutex; int /*<<< orphan*/  hw_init_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct dvobj_priv* rtw_zmalloc (int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct dvobj_priv *devobj_init(void)
{
	struct dvobj_priv *pdvobj = NULL;

	pdvobj = rtw_zmalloc(sizeof(*pdvobj));
	if (pdvobj == NULL)
		return NULL;

	mutex_init(&pdvobj->hw_init_mutex);
	mutex_init(&pdvobj->h2c_fwcmd_mutex);
	mutex_init(&pdvobj->setch_mutex);
	mutex_init(&pdvobj->setbw_mutex);

	spin_lock_init(&pdvobj->lock);

	pdvobj->macid[1] = true; /* macid = 1 for bc/mc stainfo */

	pdvobj->processing_dev_remove = false;

	atomic_set(&pdvobj->disable_func, 0);

	spin_lock_init(&pdvobj->cam_ctl.lock);

	return pdvobj;
}