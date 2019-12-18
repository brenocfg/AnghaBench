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
struct ceph_entity_addr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num; scalar_t__ type; } ;
struct ceph_connection {scalar_t__ state; int /*<<< orphan*/  mutex; scalar_t__ delay; int /*<<< orphan*/  peer_addr; TYPE_1__ peer_name; } ;
typedef  scalar_t__ __u8 ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 scalar_t__ CON_STATE_CLOSED ; 
 scalar_t__ CON_STATE_PREOPEN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ceph_pr_addr (struct ceph_entity_addr*) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ceph_entity_addr*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_con (struct ceph_connection*) ; 

void ceph_con_open(struct ceph_connection *con,
		   __u8 entity_type, __u64 entity_num,
		   struct ceph_entity_addr *addr)
{
	mutex_lock(&con->mutex);
	dout("con_open %p %s\n", con, ceph_pr_addr(addr));

	WARN_ON(con->state != CON_STATE_CLOSED);
	con->state = CON_STATE_PREOPEN;

	con->peer_name.type = (__u8) entity_type;
	con->peer_name.num = cpu_to_le64(entity_num);

	memcpy(&con->peer_addr, addr, sizeof(*addr));
	con->delay = 0;      /* reset backoff memory */
	mutex_unlock(&con->mutex);
	queue_con(con);
}