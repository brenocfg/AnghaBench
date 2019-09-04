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
struct cam_ctl_t {int /*<<< orphan*/  lock; scalar_t__ bitmap; } ;
struct dvobj_priv {int /*<<< orphan*/  cam_cache; struct cam_ctl_t cam_ctl; } ;
struct cam_entry_cache {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_CAM_INVALID_ALL ; 
 int TOTAL_CAM_ENTRY ; 
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void invalidate_cam_all(struct adapter *padapter)
{
	struct dvobj_priv *dvobj = adapter_to_dvobj(padapter);
	struct cam_ctl_t *cam_ctl = &dvobj->cam_ctl;

	rtw_hal_set_hwreg(padapter, HW_VAR_CAM_INVALID_ALL, NULL);

	spin_lock_bh(&cam_ctl->lock);
	cam_ctl->bitmap = 0;
	memset(dvobj->cam_cache, 0, sizeof(struct cam_entry_cache)*TOTAL_CAM_ENTRY);
	spin_unlock_bh(&cam_ctl->lock);
}