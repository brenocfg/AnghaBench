#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* hw; int /*<<< orphan*/  taglen; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* cipherfinal ) (TYPE_2__*,unsigned char*) ;int /*<<< orphan*/  (* cipherupdate ) (TYPE_2__*,unsigned char const*,size_t,unsigned char*) ;int /*<<< orphan*/  (* aadupdate ) (TYPE_2__*,unsigned char*,size_t) ;} ;
typedef  TYPE_2__ PROV_GCM_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  GCM_TAG_MAX_SIZE ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,unsigned char const*,size_t,unsigned char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,unsigned char*) ; 

int gcm_one_shot(PROV_GCM_CTX *ctx, unsigned char *aad, size_t aad_len,
                 const unsigned char *in, size_t in_len,
                 unsigned char *out, unsigned char *tag, size_t tag_len)
{
    int ret = 0;

    /* Use saved AAD */
    if (!ctx->hw->aadupdate(ctx, aad, aad_len))
        goto err;
    if (!ctx->hw->cipherupdate(ctx, in, in_len, out))
        goto err;
    ctx->taglen = GCM_TAG_MAX_SIZE;
    if (!ctx->hw->cipherfinal(ctx, tag))
        goto err;
    ret = 1;

err:
    return ret;
}