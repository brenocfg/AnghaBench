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
struct nfs_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_client_active_wq ; 
 int /*<<< orphan*/  nfs_client_init_is_complete (struct nfs_client const*) ; 
 int wait_event_killable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nfs_wait_client_init_complete(const struct nfs_client *clp)
{
	return wait_event_killable(nfs_client_active_wq,
			nfs_client_init_is_complete(clp));
}