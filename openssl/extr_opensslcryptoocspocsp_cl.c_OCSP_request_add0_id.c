#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * reqCert; } ;
struct TYPE_9__ {int /*<<< orphan*/  requestList; } ;
struct TYPE_10__ {TYPE_1__ tbsRequest; } ;
typedef  TYPE_2__ OCSP_REQUEST ;
typedef  TYPE_3__ OCSP_ONEREQ ;
typedef  int /*<<< orphan*/  OCSP_CERTID ;

/* Variables and functions */
 int /*<<< orphan*/  OCSP_CERTID_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCSP_ONEREQ_free (TYPE_3__*) ; 
 TYPE_3__* OCSP_ONEREQ_new () ; 
 int /*<<< orphan*/  sk_OCSP_ONEREQ_push (int /*<<< orphan*/ ,TYPE_3__*) ; 

OCSP_ONEREQ *OCSP_request_add0_id(OCSP_REQUEST *req, OCSP_CERTID *cid)
{
    OCSP_ONEREQ *one = NULL;

    if ((one = OCSP_ONEREQ_new()) == NULL)
        return NULL;
    OCSP_CERTID_free(one->reqCert);
    one->reqCert = cid;
    if (req && !sk_OCSP_ONEREQ_push(req->tbsRequest.requestList, one)) {
        one->reqCert = NULL; /* do not free on error */
        goto err;
    }
    return one;
 err:
    OCSP_ONEREQ_free(one);
    return NULL;
}