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
struct TYPE_3__ {int /*<<< orphan*/ * pubInfos; } ;
typedef  int /*<<< orphan*/  OSSL_CRMF_SINGLEPUBINFO ;
typedef  TYPE_1__ OSSL_CRMF_PKIPUBLICATIONINFO ;

/* Variables and functions */
 int /*<<< orphan*/  CRMF_F_OSSL_CRMF_MSG_PKIPUBLICATIONINFO_PUSH0_SINGLEPUBINFO ; 
 int /*<<< orphan*/  CRMF_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CRMFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sk_OSSL_CRMF_SINGLEPUBINFO_new_null () ; 
 int sk_OSSL_CRMF_SINGLEPUBINFO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int OSSL_CRMF_MSG_PKIPublicationInfo_push0_SinglePubInfo(
                                 OSSL_CRMF_PKIPUBLICATIONINFO *pi,
                                 OSSL_CRMF_SINGLEPUBINFO *spi)
{
    if (pi == NULL || spi == NULL) {
        CRMFerr(CRMF_F_OSSL_CRMF_MSG_PKIPUBLICATIONINFO_PUSH0_SINGLEPUBINFO,
                CRMF_R_NULL_ARGUMENT);
        return 0;
    }
    if (pi->pubInfos == NULL)
        pi->pubInfos = sk_OSSL_CRMF_SINGLEPUBINFO_new_null();
    if (pi->pubInfos == NULL)
        return 0;

    return sk_OSSL_CRMF_SINGLEPUBINFO_push(pi->pubInfos, spi);
}