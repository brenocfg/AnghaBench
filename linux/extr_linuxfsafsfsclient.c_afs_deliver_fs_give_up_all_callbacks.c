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
struct afs_call {int dummy; } ;

/* Variables and functions */
 int afs_transfer_reply (struct afs_call*) ; 

__attribute__((used)) static int afs_deliver_fs_give_up_all_callbacks(struct afs_call *call)
{
	return afs_transfer_reply(call);
}