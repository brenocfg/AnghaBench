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
struct TCP_Server_Info {TYPE_1__* ops; } ;
struct TYPE_2__ {int* (* get_credits_field ) (struct TCP_Server_Info*,int const) ;} ;

/* Variables and functions */
 int const CIFS_ECHO_OP ; 
 int EAGAIN ; 
 int* stub1 (struct TCP_Server_Info*,int const) ; 
 int wait_for_free_credits (struct TCP_Server_Info*,int const,int*) ; 

__attribute__((used)) static int
wait_for_free_request(struct TCP_Server_Info *server, const int timeout,
		      const int optype)
{
	int *val;

	val = server->ops->get_credits_field(server, optype);
	/* Since an echo is already inflight, no need to wait to send another */
	if (*val <= 0 && optype == CIFS_ECHO_OP)
		return -EAGAIN;
	return wait_for_free_credits(server, timeout, val);
}