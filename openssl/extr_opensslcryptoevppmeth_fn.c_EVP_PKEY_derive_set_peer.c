#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ type; } ;
struct TYPE_17__ {scalar_t__ operation; TYPE_3__* peerkey; TYPE_1__* pmeth; TYPE_13__* pkey; } ;
struct TYPE_16__ {int (* ctrl ) (TYPE_2__*,int /*<<< orphan*/ ,int,TYPE_3__*) ;scalar_t__ decrypt; scalar_t__ encrypt; scalar_t__ derive; } ;
struct TYPE_15__ {scalar_t__ type; } ;
typedef  TYPE_2__ EVP_PKEY_CTX ;
typedef  TYPE_3__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_PKEY_DERIVE_SET_PEER ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_PEER_KEY ; 
 scalar_t__ EVP_PKEY_OP_DECRYPT ; 
 scalar_t__ EVP_PKEY_OP_DERIVE ; 
 scalar_t__ EVP_PKEY_OP_ENCRYPT ; 
 int /*<<< orphan*/  EVP_PKEY_cmp_parameters (TYPE_13__*,TYPE_3__*) ; 
 int /*<<< orphan*/  EVP_PKEY_free (TYPE_3__*) ; 
 int /*<<< orphan*/  EVP_PKEY_missing_parameters (TYPE_3__*) ; 
 int /*<<< orphan*/  EVP_PKEY_up_ref (TYPE_3__*) ; 
 int /*<<< orphan*/  EVP_R_DIFFERENT_KEY_TYPES ; 
 int /*<<< orphan*/  EVP_R_DIFFERENT_PARAMETERS ; 
 int /*<<< orphan*/  EVP_R_NO_KEY_SET ; 
 int /*<<< orphan*/  EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE ; 
 int /*<<< orphan*/  EVP_R_OPERATON_NOT_INITIALIZED ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int stub2 (TYPE_2__*,int /*<<< orphan*/ ,int,TYPE_3__*) ; 

int EVP_PKEY_derive_set_peer(EVP_PKEY_CTX *ctx, EVP_PKEY *peer)
{
    int ret;
    if (!ctx || !ctx->pmeth
        || !(ctx->pmeth->derive || ctx->pmeth->encrypt || ctx->pmeth->decrypt)
        || !ctx->pmeth->ctrl) {
        EVPerr(EVP_F_EVP_PKEY_DERIVE_SET_PEER,
               EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
        return -2;
    }
    if (ctx->operation != EVP_PKEY_OP_DERIVE
        && ctx->operation != EVP_PKEY_OP_ENCRYPT
        && ctx->operation != EVP_PKEY_OP_DECRYPT) {
        EVPerr(EVP_F_EVP_PKEY_DERIVE_SET_PEER,
               EVP_R_OPERATON_NOT_INITIALIZED);
        return -1;
    }

    ret = ctx->pmeth->ctrl(ctx, EVP_PKEY_CTRL_PEER_KEY, 0, peer);

    if (ret <= 0)
        return ret;

    if (ret == 2)
        return 1;

    if (!ctx->pkey) {
        EVPerr(EVP_F_EVP_PKEY_DERIVE_SET_PEER, EVP_R_NO_KEY_SET);
        return -1;
    }

    if (ctx->pkey->type != peer->type) {
        EVPerr(EVP_F_EVP_PKEY_DERIVE_SET_PEER, EVP_R_DIFFERENT_KEY_TYPES);
        return -1;
    }

    /*
     * For clarity.  The error is if parameters in peer are
     * present (!missing) but don't match.  EVP_PKEY_cmp_parameters may return
     * 1 (match), 0 (don't match) and -2 (comparison is not defined).  -1
     * (different key types) is impossible here because it is checked earlier.
     * -2 is OK for us here, as well as 1, so we can check for 0 only.
     */
    if (!EVP_PKEY_missing_parameters(peer) &&
        !EVP_PKEY_cmp_parameters(ctx->pkey, peer)) {
        EVPerr(EVP_F_EVP_PKEY_DERIVE_SET_PEER, EVP_R_DIFFERENT_PARAMETERS);
        return -1;
    }

    EVP_PKEY_free(ctx->peerkey);
    ctx->peerkey = peer;

    ret = ctx->pmeth->ctrl(ctx, EVP_PKEY_CTRL_PEER_KEY, 1, peer);

    if (ret <= 0) {
        ctx->peerkey = NULL;
        return ret;
    }

    EVP_PKEY_up_ref(peer);
    return 1;
}