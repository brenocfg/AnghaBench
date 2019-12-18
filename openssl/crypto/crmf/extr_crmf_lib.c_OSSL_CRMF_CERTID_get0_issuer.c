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
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_7__ {TYPE_2__* issuer; } ;
struct TYPE_5__ {int /*<<< orphan*/ * directoryName; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ d; } ;
typedef  TYPE_3__ OSSL_CRMF_CERTID ;

/* Variables and functions */
 scalar_t__ GEN_DIRNAME ; 

X509_NAME *OSSL_CRMF_CERTID_get0_issuer(const OSSL_CRMF_CERTID *cid)
{
    return cid != NULL && cid->issuer->type == GEN_DIRNAME ?
        cid->issuer->d.directoryName : NULL;
}