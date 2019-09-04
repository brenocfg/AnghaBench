#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* md_data; } ;
struct TYPE_4__ {int md_size; } ;
typedef  TYPE_1__ KECCAK1600_CTX ;
typedef  TYPE_2__ EVP_MD_CTX ;

/* Variables and functions */
#define  EVP_MD_CTRL_XOF_LEN 128 

__attribute__((used)) static int shake_ctrl(EVP_MD_CTX *evp_ctx, int cmd, int p1, void *p2)
{
    KECCAK1600_CTX *ctx = evp_ctx->md_data;

    switch (cmd) {
    case EVP_MD_CTRL_XOF_LEN:
        ctx->md_size = p1;
        return 1;
    default:
        return 0;
    }
}