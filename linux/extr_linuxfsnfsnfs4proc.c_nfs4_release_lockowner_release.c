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
struct nfs_release_lockowner_data {int /*<<< orphan*/  lsp; int /*<<< orphan*/  server; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  nfs4_free_lock_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs4_release_lockowner_release(void *calldata)
{
	struct nfs_release_lockowner_data *data = calldata;
	nfs4_free_lock_state(data->server, data->lsp);
	kfree(calldata);
}