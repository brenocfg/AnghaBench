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
struct afs_call {int /*<<< orphan*/  vlserver; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  afs_flat_call_destructor (struct afs_call*) ; 
 int /*<<< orphan*/  afs_put_vlserver (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void afs_destroy_vl_get_capabilities(struct afs_call *call)
{
	afs_put_vlserver(call->net, call->vlserver);
	afs_flat_call_destructor(call);
}