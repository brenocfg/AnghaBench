#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  get_entropy; TYPE_1__* drbg; } ;
struct TYPE_8__ {int /*<<< orphan*/  get_entropy; } ;
typedef  TYPE_1__ RAND_DRBG ;
typedef  TYPE_2__ HOOK_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  RAND_DRBG_set_ex_data (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  app_data_index ; 
 int /*<<< orphan*/  get_entropy_hook ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hook_drbg(RAND_DRBG *drbg, HOOK_CTX *ctx)
{
    memset(ctx, 0, sizeof(*ctx));
    ctx->drbg = drbg;
    ctx->get_entropy = drbg->get_entropy;
    drbg->get_entropy = get_entropy_hook;
    RAND_DRBG_set_ex_data(drbg, app_data_index, ctx);
}