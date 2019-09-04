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
struct TYPE_2__ {int /*<<< orphan*/  (* shutdown ) () ;} ;

/* Variables and functions */
 TYPE_1__* hmcdrv_ftp_funcs ; 
 int /*<<< orphan*/  hmcdrv_ftp_mutex ; 
 scalar_t__ hmcdrv_ftp_refcnt ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 

void hmcdrv_ftp_shutdown(void)
{
	mutex_lock(&hmcdrv_ftp_mutex);
	--hmcdrv_ftp_refcnt;

	if ((hmcdrv_ftp_refcnt == 0) && hmcdrv_ftp_funcs)
		hmcdrv_ftp_funcs->shutdown();

	mutex_unlock(&hmcdrv_ftp_mutex);
}