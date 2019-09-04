#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tmpcipher; int /*<<< orphan*/  tmpengine; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ EVP_MAC_IMPL ;

/* Variables and functions */
 int /*<<< orphan*/  CMAC_CTX_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmac_copy(EVP_MAC_IMPL *cdst, EVP_MAC_IMPL *csrc)
{
    if (!CMAC_CTX_copy(cdst->ctx, csrc->ctx))
        return 0;

    cdst->tmpengine = csrc->tmpengine;
    cdst->tmpcipher = csrc->tmpcipher;
    return 1;
}