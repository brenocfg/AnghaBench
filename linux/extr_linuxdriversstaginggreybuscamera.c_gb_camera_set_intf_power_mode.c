#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct gb_svc {int dummy; } ;
struct gb_camera {TYPE_2__* connection; } ;
struct TYPE_4__ {TYPE_1__* hd; } ;
struct TYPE_3__ {struct gb_svc* svc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_SVC_NO_DE_EMPHASIS ; 
 int GB_SVC_PWRM_RXTERMINATION ; 
 int GB_SVC_PWRM_TXTERMINATION ; 
 int /*<<< orphan*/  GB_SVC_SMALL_AMPLITUDE ; 
 int /*<<< orphan*/  GB_SVC_UNIPRO_FAST_MODE ; 
 int /*<<< orphan*/  GB_SVC_UNIPRO_HS_SERIES_A ; 
 int /*<<< orphan*/  GB_SVC_UNIPRO_SLOW_AUTO_MODE ; 
 int gb_svc_intf_set_power_mode (struct gb_svc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_camera_set_intf_power_mode(struct gb_camera *gcam, u8 intf_id,
					 bool hs)
{
	struct gb_svc *svc = gcam->connection->hd->svc;
	int ret;

	if (hs)
		ret = gb_svc_intf_set_power_mode(svc, intf_id,
						 GB_SVC_UNIPRO_HS_SERIES_A,
						 GB_SVC_UNIPRO_FAST_MODE, 2, 2,
						 GB_SVC_SMALL_AMPLITUDE,
						 GB_SVC_NO_DE_EMPHASIS,
						 GB_SVC_UNIPRO_FAST_MODE, 2, 2,
						 GB_SVC_PWRM_RXTERMINATION |
						 GB_SVC_PWRM_TXTERMINATION, 0,
						 NULL, NULL);
	else
		ret = gb_svc_intf_set_power_mode(svc, intf_id,
						 GB_SVC_UNIPRO_HS_SERIES_A,
						 GB_SVC_UNIPRO_SLOW_AUTO_MODE,
						 2, 1,
						 GB_SVC_SMALL_AMPLITUDE,
						 GB_SVC_NO_DE_EMPHASIS,
						 GB_SVC_UNIPRO_SLOW_AUTO_MODE,
						 2, 1,
						 0, 0,
						 NULL, NULL);

	return ret;
}