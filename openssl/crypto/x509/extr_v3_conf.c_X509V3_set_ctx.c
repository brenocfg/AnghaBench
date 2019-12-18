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
typedef  int /*<<< orphan*/  X509_REQ ;
typedef  int /*<<< orphan*/  X509_CRL ;
struct TYPE_3__ {int flags; int /*<<< orphan*/ * subject_req; int /*<<< orphan*/ * crl; int /*<<< orphan*/ * subject_cert; int /*<<< orphan*/ * issuer_cert; } ;
typedef  TYPE_1__ X509V3_CTX ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */

void X509V3_set_ctx(X509V3_CTX *ctx, X509 *issuer, X509 *subj, X509_REQ *req,
                    X509_CRL *crl, int flags)
{
    ctx->issuer_cert = issuer;
    ctx->subject_cert = subj;
    ctx->crl = crl;
    ctx->subject_req = req;
    ctx->flags = flags;
}