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
struct rds_message {int /*<<< orphan*/  m_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  rdsdebug (char*,struct rds_message*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 

void rds_message_addref(struct rds_message *rm)
{
	rdsdebug("addref rm %p ref %d\n", rm, refcount_read(&rm->m_refcount));
	refcount_inc(&rm->m_refcount);
}