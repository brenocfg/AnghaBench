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
struct TYPE_2__ {int /*<<< orphan*/ * ies; scalar_t__ ies_len; int /*<<< orphan*/ * bssid; int /*<<< orphan*/ * ssid; scalar_t__ ssid_len; } ;
struct host_if_drv {TYPE_1__ usr_conn_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void host_int_free_user_conn_req(struct host_if_drv *hif_drv)
{
	hif_drv->usr_conn_req.ssid_len = 0;
	kfree(hif_drv->usr_conn_req.ssid);
	hif_drv->usr_conn_req.ssid = NULL;
	kfree(hif_drv->usr_conn_req.bssid);
	hif_drv->usr_conn_req.bssid = NULL;
	hif_drv->usr_conn_req.ies_len = 0;
	kfree(hif_drv->usr_conn_req.ies);
	hif_drv->usr_conn_req.ies = NULL;
}