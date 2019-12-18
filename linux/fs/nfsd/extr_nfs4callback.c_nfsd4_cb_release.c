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
struct nfsd4_callback {TYPE_1__* cb_ops; scalar_t__ cb_need_restart; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release ) (struct nfsd4_callback*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nfsd4_run_cb (struct nfsd4_callback*) ; 
 int /*<<< orphan*/  stub1 (struct nfsd4_callback*) ; 

__attribute__((used)) static void nfsd4_cb_release(void *calldata)
{
	struct nfsd4_callback *cb = calldata;

	if (cb->cb_need_restart)
		nfsd4_run_cb(cb);
	else
		cb->cb_ops->release(cb);

}