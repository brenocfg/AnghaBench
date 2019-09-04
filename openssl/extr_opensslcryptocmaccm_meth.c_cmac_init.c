#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * tmpengine; int /*<<< orphan*/ * tmpcipher; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ EVP_MAC_IMPL ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int CMAC_Init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmac_init(EVP_MAC_IMPL *cctx)
{
    int rv = CMAC_Init(cctx->ctx, NULL, 0, cctx->tmpcipher,
                       (ENGINE *)cctx->tmpengine);
    cctx->tmpcipher = NULL;
    cctx->tmpengine = NULL;

    return rv;
}