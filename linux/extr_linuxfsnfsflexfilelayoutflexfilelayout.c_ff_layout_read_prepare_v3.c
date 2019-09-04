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
struct rpc_task {int dummy; } ;
struct nfs_pgio_header {int dummy; } ;

/* Variables and functions */
 scalar_t__ ff_layout_read_prepare_common (struct rpc_task*,struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  rpc_call_start (struct rpc_task*) ; 

__attribute__((used)) static void ff_layout_read_prepare_v3(struct rpc_task *task, void *data)
{
	struct nfs_pgio_header *hdr = data;

	if (ff_layout_read_prepare_common(task, hdr))
		return;

	rpc_call_start(task);
}