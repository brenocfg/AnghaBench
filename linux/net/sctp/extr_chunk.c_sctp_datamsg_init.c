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
struct sctp_datamsg {int can_delay; int /*<<< orphan*/  chunks; scalar_t__ expires_at; scalar_t__ abandoned; scalar_t__ send_error; scalar_t__ send_failed; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void sctp_datamsg_init(struct sctp_datamsg *msg)
{
	refcount_set(&msg->refcnt, 1);
	msg->send_failed = 0;
	msg->send_error = 0;
	msg->can_delay = 1;
	msg->abandoned = 0;
	msg->expires_at = 0;
	INIT_LIST_HEAD(&msg->chunks);
}