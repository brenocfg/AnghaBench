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
typedef  int /*<<< orphan*/  umode_t ;
struct mq_attr {int dummy; } ;
struct TYPE_2__ {int oflag; int /*<<< orphan*/  mode; int /*<<< orphan*/  attr; } ;
struct audit_context {int /*<<< orphan*/  type; TYPE_1__ mq_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_MQ_OPEN ; 
 struct audit_context* audit_context () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mq_attr*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void __audit_mq_open(int oflag, umode_t mode, struct mq_attr *attr)
{
	struct audit_context *context = audit_context();

	if (attr)
		memcpy(&context->mq_open.attr, attr, sizeof(struct mq_attr));
	else
		memset(&context->mq_open.attr, 0, sizeof(struct mq_attr));

	context->mq_open.oflag = oflag;
	context->mq_open.mode = mode;

	context->type = AUDIT_MQ_OPEN;
}