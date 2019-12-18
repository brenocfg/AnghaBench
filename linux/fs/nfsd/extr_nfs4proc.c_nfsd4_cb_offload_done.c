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
struct nfsd4_callback {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int nfsd4_cb_offload_done(struct nfsd4_callback *cb,
				 struct rpc_task *task)
{
	return 1;
}