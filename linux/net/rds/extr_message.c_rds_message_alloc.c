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
struct scatterlist {int dummy; } ;
struct rds_message {unsigned int m_total_sgs; int /*<<< orphan*/  m_flush_wait; int /*<<< orphan*/  m_rs_lock; int /*<<< orphan*/  m_conn_item; int /*<<< orphan*/  m_sock_item; int /*<<< orphan*/  m_refcount; scalar_t__ m_used_sgs; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int KMALLOC_MAX_SIZE ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct rds_message* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct rds_message *rds_message_alloc(unsigned int extra_len, gfp_t gfp)
{
	struct rds_message *rm;

	if (extra_len > KMALLOC_MAX_SIZE - sizeof(struct rds_message))
		return NULL;

	rm = kzalloc(sizeof(struct rds_message) + extra_len, gfp);
	if (!rm)
		goto out;

	rm->m_used_sgs = 0;
	rm->m_total_sgs = extra_len / sizeof(struct scatterlist);

	refcount_set(&rm->m_refcount, 1);
	INIT_LIST_HEAD(&rm->m_sock_item);
	INIT_LIST_HEAD(&rm->m_conn_item);
	spin_lock_init(&rm->m_rs_lock);
	init_waitqueue_head(&rm->m_flush_wait);

out:
	return rm;
}