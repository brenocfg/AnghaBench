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
struct TYPE_4__ {int /*<<< orphan*/  tmpmd; int /*<<< orphan*/  tmpengine; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ EVP_MAC_IMPL ;

/* Variables and functions */
 int /*<<< orphan*/  HMAC_CTX_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hmac_copy(EVP_MAC_IMPL *hdst, EVP_MAC_IMPL *hsrc)
{
    if (!HMAC_CTX_copy(hdst->ctx, hsrc->ctx))
        return 0;

    hdst->tmpengine = hsrc->tmpengine;
    hdst->tmpmd = hsrc->tmpmd;
    return 1;
}