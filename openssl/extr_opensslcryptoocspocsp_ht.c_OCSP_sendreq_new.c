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
typedef  int /*<<< orphan*/  OCSP_REQ_CTX ;
typedef  int /*<<< orphan*/  OCSP_REQUEST ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  OCSP_REQ_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCSP_REQ_CTX_http (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * OCSP_REQ_CTX_new (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OCSP_REQ_CTX_set1_req (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

OCSP_REQ_CTX *OCSP_sendreq_new(BIO *io, const char *path, OCSP_REQUEST *req,
                               int maxline)
{

    OCSP_REQ_CTX *rctx = NULL;
    rctx = OCSP_REQ_CTX_new(io, maxline);
    if (rctx == NULL)
        return NULL;

    if (!OCSP_REQ_CTX_http(rctx, "POST", path))
        goto err;

    if (req && !OCSP_REQ_CTX_set1_req(rctx, req))
        goto err;

    return rctx;

 err:
    OCSP_REQ_CTX_free(rctx);
    return NULL;
}