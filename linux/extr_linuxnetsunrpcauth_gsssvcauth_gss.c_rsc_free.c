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
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct rsc {int /*<<< orphan*/  cred; scalar_t__ mechctx; TYPE_1__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_svc_cred (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_delete_sec_context (scalar_t__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rsc_free(struct rsc *rsci)
{
	kfree(rsci->handle.data);
	if (rsci->mechctx)
		gss_delete_sec_context(&rsci->mechctx);
	free_svc_cred(&rsci->cred);
}