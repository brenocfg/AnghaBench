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
struct scsi_device {struct alua_dh_data* handler_data; } ;
struct alua_port_group {int /*<<< orphan*/  kref; } ;
struct alua_dh_data {int /*<<< orphan*/  pg; } ;

/* Variables and functions */
 int /*<<< orphan*/  alua_rtpg_queue (struct alua_port_group*,struct scsi_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct alua_port_group* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  release_port_group ; 

__attribute__((used)) static void alua_check(struct scsi_device *sdev, bool force)
{
	struct alua_dh_data *h = sdev->handler_data;
	struct alua_port_group *pg;

	rcu_read_lock();
	pg = rcu_dereference(h->pg);
	if (!pg || !kref_get_unless_zero(&pg->kref)) {
		rcu_read_unlock();
		return;
	}
	rcu_read_unlock();

	alua_rtpg_queue(pg, sdev, NULL, force);
	kref_put(&pg->kref, release_port_group);
}