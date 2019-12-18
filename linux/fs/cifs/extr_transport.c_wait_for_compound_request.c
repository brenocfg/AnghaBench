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
struct TCP_Server_Info {int in_flight; int /*<<< orphan*/  req_lock; TYPE_1__* ops; } ;
struct TYPE_2__ {int* (* get_credits_field ) (struct TCP_Server_Info*,int const) ;} ;

/* Variables and functions */
 int const CIFS_OP_MASK ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int* stub1 (struct TCP_Server_Info*,int const) ; 
 int wait_for_free_credits (struct TCP_Server_Info*,int,int,int const,unsigned int*) ; 

__attribute__((used)) static int
wait_for_compound_request(struct TCP_Server_Info *server, int num,
			  const int flags, unsigned int *instance)
{
	int *credits;

	credits = server->ops->get_credits_field(server, flags & CIFS_OP_MASK);

	spin_lock(&server->req_lock);
	if (*credits < num) {
		/*
		 * Return immediately if not too many requests in flight since
		 * we will likely be stuck on waiting for credits.
		 */
		if (server->in_flight < num - *credits) {
			spin_unlock(&server->req_lock);
			return -ENOTSUPP;
		}
	}
	spin_unlock(&server->req_lock);

	return wait_for_free_credits(server, num, 60000, flags,
				     instance);
}