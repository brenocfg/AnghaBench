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
struct svc_rqst {int /*<<< orphan*/  rq_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RQ_SECURE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_addr (struct svc_rqst*) ; 
 scalar_t__ svc_port_is_privileged (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void svc_sock_secure_port(struct svc_rqst *rqstp)
{
	if (svc_port_is_privileged(svc_addr(rqstp)))
		set_bit(RQ_SECURE, &rqstp->rq_flags);
	else
		clear_bit(RQ_SECURE, &rqstp->rq_flags);
}