#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  algorithm; } ;
struct TYPE_6__ {TYPE_1__ sig_alg; } ;
struct TYPE_7__ {TYPE_2__ crl; } ;
typedef  TYPE_3__ X509_CRL ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 unsigned long X509_V_FLAG_SUITEB_128_LOS ; 
 int X509_V_OK ; 
 int check_suite_b (int /*<<< orphan*/ *,int,unsigned long*) ; 

int X509_CRL_check_suiteb(X509_CRL *crl, EVP_PKEY *pk, unsigned long flags)
{
    int sign_nid;
    if (!(flags & X509_V_FLAG_SUITEB_128_LOS))
        return X509_V_OK;
    sign_nid = OBJ_obj2nid(crl->crl.sig_alg.algorithm);
    return check_suite_b(pk, sign_nid, &flags);
}