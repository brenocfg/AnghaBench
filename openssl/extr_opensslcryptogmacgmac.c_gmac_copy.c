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
struct TYPE_4__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  engine; int /*<<< orphan*/  cipher; } ;
typedef  TYPE_1__ EVP_MAC_IMPL ;

/* Variables and functions */
 int EVP_CIPHER_CTX_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gmac_copy(EVP_MAC_IMPL *gdst, EVP_MAC_IMPL *gsrc)
{
    gdst->cipher = gsrc->cipher;
    gdst->engine = gsrc->engine;
    return EVP_CIPHER_CTX_copy(gdst->ctx, gsrc->ctx);
}