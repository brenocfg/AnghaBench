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
typedef  scalar_t__ u64 ;
struct TYPE_4__ {TYPE_1__* osdmap; } ;
struct ceph_client {int /*<<< orphan*/  monc; TYPE_2__ osdc; } ;
struct TYPE_3__ {scalar_t__ epoch; } ;

/* Variables and functions */
 int ceph_monc_get_version (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int ceph_monc_wait_osdmap (int /*<<< orphan*/ *,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  ceph_osdc_maybe_request_map (TYPE_2__*) ; 

int ceph_wait_for_latest_osdmap(struct ceph_client *client,
				unsigned long timeout)
{
	u64 newest_epoch;
	int ret;

	ret = ceph_monc_get_version(&client->monc, "osdmap", &newest_epoch);
	if (ret)
		return ret;

	if (client->osdc.osdmap->epoch >= newest_epoch)
		return 0;

	ceph_osdc_maybe_request_map(&client->osdc);
	return ceph_monc_wait_osdmap(&client->monc, newest_epoch, timeout);
}