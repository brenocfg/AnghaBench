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
struct ipr_ioa_cfg {scalar_t__ sdt_state; int in_ioa_bringdown; scalar_t__ reset_retries; } ;
typedef  enum ipr_shutdown_type { ____Placeholder_ipr_shutdown_type } ipr_shutdown_type ;

/* Variables and functions */
 scalar_t__ ABORT_DUMP ; 
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  LEAVE ; 
 scalar_t__ WAIT_FOR_DUMP ; 
 int /*<<< orphan*/  ipr_initiate_ioa_reset (struct ipr_ioa_cfg*,int) ; 

__attribute__((used)) static void ipr_initiate_ioa_bringdown(struct ipr_ioa_cfg *ioa_cfg,
				       enum ipr_shutdown_type shutdown_type)
{
	ENTER;
	if (ioa_cfg->sdt_state == WAIT_FOR_DUMP)
		ioa_cfg->sdt_state = ABORT_DUMP;
	ioa_cfg->reset_retries = 0;
	ioa_cfg->in_ioa_bringdown = 1;
	ipr_initiate_ioa_reset(ioa_cfg, shutdown_type);
	LEAVE;
}