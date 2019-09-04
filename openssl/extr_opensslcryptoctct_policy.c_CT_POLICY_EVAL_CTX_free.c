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
struct TYPE_4__ {int /*<<< orphan*/  issuer; int /*<<< orphan*/  cert; } ;
typedef  TYPE_1__ CT_POLICY_EVAL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ ) ; 

void CT_POLICY_EVAL_CTX_free(CT_POLICY_EVAL_CTX *ctx)
{
    if (ctx == NULL)
        return;
    X509_free(ctx->cert);
    X509_free(ctx->issuer);
    OPENSSL_free(ctx);
}