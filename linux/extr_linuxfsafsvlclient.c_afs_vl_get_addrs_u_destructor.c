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
struct afs_server {int dummy; } ;
struct afs_call {scalar_t__* reply; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 void afs_flat_call_destructor (struct afs_call*) ; 
 int /*<<< orphan*/  afs_put_server (int /*<<< orphan*/ ,struct afs_server*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 

__attribute__((used)) static void afs_vl_get_addrs_u_destructor(struct afs_call *call)
{
	afs_put_server(call->net, (struct afs_server *)call->reply[0]);
	kfree(call->reply[1]);
	return afs_flat_call_destructor(call);
}