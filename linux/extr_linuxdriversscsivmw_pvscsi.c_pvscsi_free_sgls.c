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
struct pvscsi_ctx {scalar_t__ sgl; } ;
struct pvscsi_adapter {unsigned int req_depth; struct pvscsi_ctx* cmd_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGL_SIZE ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pvscsi_free_sgls(const struct pvscsi_adapter *adapter)
{
	struct pvscsi_ctx *ctx = adapter->cmd_map;
	unsigned i;

	for (i = 0; i < adapter->req_depth; ++i, ++ctx)
		free_pages((unsigned long)ctx->sgl, get_order(SGL_SIZE));
}