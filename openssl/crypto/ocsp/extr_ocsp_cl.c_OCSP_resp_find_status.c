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
typedef  int /*<<< orphan*/  OCSP_SINGLERESP ;
typedef  int /*<<< orphan*/  OCSP_CERTID ;
typedef  int /*<<< orphan*/  OCSP_BASICRESP ;
typedef  int /*<<< orphan*/  ASN1_GENERALIZEDTIME ;

/* Variables and functions */
 int OCSP_resp_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * OCSP_resp_get0 (int /*<<< orphan*/ *,int) ; 
 int OCSP_single_get0_status (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

int OCSP_resp_find_status(OCSP_BASICRESP *bs, OCSP_CERTID *id, int *status,
                          int *reason,
                          ASN1_GENERALIZEDTIME **revtime,
                          ASN1_GENERALIZEDTIME **thisupd,
                          ASN1_GENERALIZEDTIME **nextupd)
{
    int i;
    OCSP_SINGLERESP *single;
    i = OCSP_resp_find(bs, id, -1);
    /* Maybe check for multiple responses and give an error? */
    if (i < 0)
        return 0;
    single = OCSP_resp_get0(bs, i);
    i = OCSP_single_get0_status(single, reason, revtime, thisupd, nextupd);
    if (status)
        *status = i;
    return 1;
}