#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int idp_reasons; int /*<<< orphan*/  idp_flags; } ;
typedef  TYPE_2__ X509_CRL ;
struct TYPE_9__ {scalar_t__ onlyuser; scalar_t__ onlyCA; scalar_t__ onlyattr; scalar_t__ indirectCRL; int /*<<< orphan*/  distpoint; TYPE_1__* onlysomereasons; } ;
struct TYPE_7__ {int length; int* data; } ;
typedef  TYPE_3__ ISSUING_DIST_POINT ;

/* Variables and functions */
 int CRLDP_ALL_REASONS ; 
 int /*<<< orphan*/  DIST_POINT_set_dpname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDP_INDIRECT ; 
 int /*<<< orphan*/  IDP_INVALID ; 
 int /*<<< orphan*/  IDP_ONLYATTR ; 
 int /*<<< orphan*/  IDP_ONLYCA ; 
 int /*<<< orphan*/  IDP_ONLYUSER ; 
 int /*<<< orphan*/  IDP_PRESENT ; 
 int /*<<< orphan*/  IDP_REASONS ; 
 int /*<<< orphan*/  X509_CRL_get_issuer (TYPE_2__*) ; 

__attribute__((used)) static void setup_idp(X509_CRL *crl, ISSUING_DIST_POINT *idp)
{
    int idp_only = 0;
    /* Set various flags according to IDP */
    crl->idp_flags |= IDP_PRESENT;
    if (idp->onlyuser > 0) {
        idp_only++;
        crl->idp_flags |= IDP_ONLYUSER;
    }
    if (idp->onlyCA > 0) {
        idp_only++;
        crl->idp_flags |= IDP_ONLYCA;
    }
    if (idp->onlyattr > 0) {
        idp_only++;
        crl->idp_flags |= IDP_ONLYATTR;
    }

    if (idp_only > 1)
        crl->idp_flags |= IDP_INVALID;

    if (idp->indirectCRL > 0)
        crl->idp_flags |= IDP_INDIRECT;

    if (idp->onlysomereasons) {
        crl->idp_flags |= IDP_REASONS;
        if (idp->onlysomereasons->length > 0)
            crl->idp_reasons = idp->onlysomereasons->data[0];
        if (idp->onlysomereasons->length > 1)
            crl->idp_reasons |= (idp->onlysomereasons->data[1] << 8);
        crl->idp_reasons &= CRLDP_ALL_REASONS;
    }

    DIST_POINT_set_dpname(idp->distpoint, X509_CRL_get_issuer(crl));
}