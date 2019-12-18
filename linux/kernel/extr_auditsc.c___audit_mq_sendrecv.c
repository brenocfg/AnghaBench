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
struct timespec64 {int dummy; } ;
struct TYPE_2__ {size_t msg_len; unsigned int msg_prio; int /*<<< orphan*/  mqdes; struct timespec64 abs_timeout; } ;
struct audit_context {int /*<<< orphan*/  type; TYPE_1__ mq_sendrecv; } ;
typedef  int /*<<< orphan*/  mqd_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_MQ_SENDRECV ; 
 struct audit_context* audit_context () ; 
 int /*<<< orphan*/  memcpy (struct timespec64*,struct timespec64 const*,int) ; 
 int /*<<< orphan*/  memset (struct timespec64*,int /*<<< orphan*/ ,int) ; 

void __audit_mq_sendrecv(mqd_t mqdes, size_t msg_len, unsigned int msg_prio,
			const struct timespec64 *abs_timeout)
{
	struct audit_context *context = audit_context();
	struct timespec64 *p = &context->mq_sendrecv.abs_timeout;

	if (abs_timeout)
		memcpy(p, abs_timeout, sizeof(*p));
	else
		memset(p, 0, sizeof(*p));

	context->mq_sendrecv.mqdes = mqdes;
	context->mq_sendrecv.msg_len = msg_len;
	context->mq_sendrecv.msg_prio = msg_prio;

	context->type = AUDIT_MQ_SENDRECV;
}