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
struct TYPE_3__ {int /*<<< orphan*/ * cert; } ;
typedef  TYPE_1__ CT_POLICY_EVAL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  X509_up_ref (int /*<<< orphan*/ *) ; 

int CT_POLICY_EVAL_CTX_set1_cert(CT_POLICY_EVAL_CTX *ctx, X509 *cert)
{
    if (!X509_up_ref(cert))
        return 0;
    ctx->cert = cert;
    return 1;
}