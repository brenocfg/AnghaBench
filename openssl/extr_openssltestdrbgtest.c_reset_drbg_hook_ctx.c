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

/* Variables and functions */
 int /*<<< orphan*/  master_ctx ; 
 int /*<<< orphan*/  private_ctx ; 
 int /*<<< orphan*/  public_ctx ; 
 int /*<<< orphan*/  reset_hook_ctx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reset_drbg_hook_ctx(void)
{
    reset_hook_ctx(&master_ctx);
    reset_hook_ctx(&public_ctx);
    reset_hook_ctx(&private_ctx);
}