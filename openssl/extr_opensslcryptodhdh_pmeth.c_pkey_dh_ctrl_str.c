#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int rfc5114_param; int param_nid; } ;
struct TYPE_9__ {TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_PKEY_CTX ;
typedef  TYPE_2__ DH_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  DH_F_PKEY_DH_CTRL_STR ; 
 int /*<<< orphan*/  DH_R_INVALID_PARAMETER_NAME ; 
 int /*<<< orphan*/  DHerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EVP_PKEY_CTX_set_dh_pad (TYPE_1__*,int) ; 
 int EVP_PKEY_CTX_set_dh_paramgen_generator (TYPE_1__*,int) ; 
 int EVP_PKEY_CTX_set_dh_paramgen_prime_len (TYPE_1__*,int) ; 
 int EVP_PKEY_CTX_set_dh_paramgen_subprime_len (TYPE_1__*,int) ; 
 int EVP_PKEY_CTX_set_dh_paramgen_type (TYPE_1__*,int) ; 
 int NID_undef ; 
 int OBJ_sn2nid (char const*) ; 
 int atoi (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int pkey_dh_ctrl_str(EVP_PKEY_CTX *ctx,
                            const char *type, const char *value)
{
    if (strcmp(type, "dh_paramgen_prime_len") == 0) {
        int len;
        len = atoi(value);
        return EVP_PKEY_CTX_set_dh_paramgen_prime_len(ctx, len);
    }
    if (strcmp(type, "dh_rfc5114") == 0) {
        DH_PKEY_CTX *dctx = ctx->data;
        int len;
        len = atoi(value);
        if (len < 0 || len > 3)
            return -2;
        dctx->rfc5114_param = len;
        return 1;
    }
    if (strcmp(type, "dh_param") == 0) {
        DH_PKEY_CTX *dctx = ctx->data;
        int nid = OBJ_sn2nid(value);

        if (nid == NID_undef) {
            DHerr(DH_F_PKEY_DH_CTRL_STR, DH_R_INVALID_PARAMETER_NAME);
            return -2;
        }
        dctx->param_nid = nid;
        return 1;
    }
    if (strcmp(type, "dh_paramgen_generator") == 0) {
        int len;
        len = atoi(value);
        return EVP_PKEY_CTX_set_dh_paramgen_generator(ctx, len);
    }
    if (strcmp(type, "dh_paramgen_subprime_len") == 0) {
        int len;
        len = atoi(value);
        return EVP_PKEY_CTX_set_dh_paramgen_subprime_len(ctx, len);
    }
    if (strcmp(type, "dh_paramgen_type") == 0) {
        int typ;
        typ = atoi(value);
        return EVP_PKEY_CTX_set_dh_paramgen_type(ctx, typ);
    }
    if (strcmp(type, "dh_pad") == 0) {
        int pad;
        pad = atoi(value);
        return EVP_PKEY_CTX_set_dh_pad(ctx, pad);
    }
    return -2;
}