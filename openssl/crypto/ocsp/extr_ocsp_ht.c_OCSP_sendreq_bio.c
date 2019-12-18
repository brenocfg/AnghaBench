#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OCSP_RESPONSE ;
typedef  int /*<<< orphan*/  OCSP_REQ_CTX ;
typedef  int /*<<< orphan*/  OCSP_REQUEST ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ BIO_should_retry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCSP_REQ_CTX_free (int /*<<< orphan*/ *) ; 
 int OCSP_sendreq_nbio (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OCSP_sendreq_new (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int) ; 

OCSP_RESPONSE *OCSP_sendreq_bio(BIO *b, const char *path, OCSP_REQUEST *req)
{
    OCSP_RESPONSE *resp = NULL;
    OCSP_REQ_CTX *ctx;
    int rv;

    ctx = OCSP_sendreq_new(b, path, req, -1);

    if (ctx == NULL)
        return NULL;

    do {
        rv = OCSP_sendreq_nbio(&resp, ctx);
    } while ((rv == -1) && BIO_should_retry(b));

    OCSP_REQ_CTX_free(ctx);

    if (rv)
        return resp;

    return NULL;
}