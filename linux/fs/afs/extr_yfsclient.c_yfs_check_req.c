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
struct afs_call {void* request; size_t request_size; TYPE_1__* type; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,size_t,size_t) ; 

__attribute__((used)) static void yfs_check_req(struct afs_call *call, __be32 *bp)
{
	size_t len = (void *)bp - call->request;

	if (len > call->request_size)
		pr_err("kAFS: %s: Request buffer overflow (%zu>%u)\n",
		       call->type->name, len, call->request_size);
	else if (len < call->request_size)
		pr_warning("kAFS: %s: Request buffer underflow (%zu<%u)\n",
			   call->type->name, len, call->request_size);
}