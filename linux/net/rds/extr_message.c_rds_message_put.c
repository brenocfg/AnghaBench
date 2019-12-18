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
struct rds_message {int /*<<< orphan*/  m_conn_item; int /*<<< orphan*/  m_sock_item; int /*<<< orphan*/  m_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN (int,char*,struct rds_message*) ; 
 int /*<<< orphan*/  kfree (struct rds_message*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_message_purge (struct rds_message*) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_message*,int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 

void rds_message_put(struct rds_message *rm)
{
	rdsdebug("put rm %p ref %d\n", rm, refcount_read(&rm->m_refcount));
	WARN(!refcount_read(&rm->m_refcount), "danger refcount zero on %p\n", rm);
	if (refcount_dec_and_test(&rm->m_refcount)) {
		BUG_ON(!list_empty(&rm->m_sock_item));
		BUG_ON(!list_empty(&rm->m_conn_item));
		rds_message_purge(rm);

		kfree(rm);
	}
}