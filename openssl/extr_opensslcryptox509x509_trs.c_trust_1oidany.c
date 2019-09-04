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
struct TYPE_3__ {int /*<<< orphan*/  arg1; } ;
typedef  TYPE_1__ X509_TRUST ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int X509_TRUST_DO_SS_COMPAT ; 
 int X509_TRUST_OK_ANY_EKU ; 
 int obj_trust (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int trust_1oidany(X509_TRUST *trust, X509 *x, int flags)
{
    /*
     * Declare the chain verified if the desired trust OID is not rejected in
     * any auxiliary trust info for this certificate, and the OID is either
     * expressly trusted, or else either "anyEKU" is trusted, or the
     * certificate is self-signed.
     */
    flags |= X509_TRUST_DO_SS_COMPAT | X509_TRUST_OK_ANY_EKU;
    return obj_trust(trust->arg1, x, flags);
}