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
struct request_sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ireq_opt; } ;

/* Variables and functions */
 TYPE_1__* inet_rsk (struct request_sock*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tcp_v4_reqsk_destructor(struct request_sock *req)
{
	kfree(rcu_dereference_protected(inet_rsk(req)->ireq_opt, 1));
}