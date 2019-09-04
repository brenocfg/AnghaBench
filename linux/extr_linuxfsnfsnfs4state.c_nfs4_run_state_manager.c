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
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  allow_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put_and_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_state_manager (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs_put_client (struct nfs_client*) ; 

__attribute__((used)) static int nfs4_run_state_manager(void *ptr)
{
	struct nfs_client *clp = ptr;

	allow_signal(SIGKILL);
	nfs4_state_manager(clp);
	nfs_put_client(clp);
	module_put_and_exit(0);
	return 0;
}