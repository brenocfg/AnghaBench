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
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_3__ {int /*<<< orphan*/ * signer_cert; } ;
typedef  TYPE_1__ TS_RESP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  TS_F_TS_RESP_CTX_SET_SIGNER_CERT ; 
 int /*<<< orphan*/  TS_R_INVALID_SIGNER_CERTIFICATE_PURPOSE ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_PURPOSE_TIMESTAMP_SIGN ; 
 int X509_check_purpose (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_up_ref (int /*<<< orphan*/ *) ; 

int TS_RESP_CTX_set_signer_cert(TS_RESP_CTX *ctx, X509 *signer)
{
    if (X509_check_purpose(signer, X509_PURPOSE_TIMESTAMP_SIGN, 0) != 1) {
        TSerr(TS_F_TS_RESP_CTX_SET_SIGNER_CERT,
              TS_R_INVALID_SIGNER_CERTIFICATE_PURPOSE);
        return 0;
    }
    X509_free(ctx->signer_cert);
    ctx->signer_cert = signer;
    X509_up_ref(ctx->signer_cert);
    return 1;
}