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
typedef  int /*<<< orphan*/  X509_EXTENSION ;
typedef  int /*<<< orphan*/  OCSP_REQUEST ;
typedef  int /*<<< orphan*/  OCSP_BASICRESP ;

/* Variables and functions */
 int /*<<< orphan*/  NID_id_pkix_OCSP_Nonce ; 
 int OCSP_BASICRESP_add_ext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * OCSP_REQUEST_get_ext (int /*<<< orphan*/ *,int) ; 
 int OCSP_REQUEST_get_ext_by_NID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int OCSP_copy_nonce(OCSP_BASICRESP *resp, OCSP_REQUEST *req)
{
    X509_EXTENSION *req_ext;
    int req_idx;
    /* Check for nonce in request */
    req_idx = OCSP_REQUEST_get_ext_by_NID(req, NID_id_pkix_OCSP_Nonce, -1);
    /* If no nonce that's OK */
    if (req_idx < 0)
        return 2;
    req_ext = OCSP_REQUEST_get_ext(req, req_idx);
    return OCSP_BASICRESP_add_ext(resp, req_ext, -1);
}