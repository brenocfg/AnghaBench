#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ trust; scalar_t__ reject; } ;
typedef  TYPE_1__ X509_CERT_AUX ;
struct TYPE_6__ {TYPE_1__* aux; } ;
typedef  TYPE_2__ X509 ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int NID_anyExtendedKeyUsage ; 
 int OBJ_obj2nid (int /*<<< orphan*/ *) ; 
 int X509_TRUST_DO_SS_COMPAT ; 
 int X509_TRUST_OK_ANY_EKU ; 
 int X509_TRUST_REJECTED ; 
 int X509_TRUST_TRUSTED ; 
 int X509_TRUST_UNTRUSTED ; 
 int sk_ASN1_OBJECT_num (scalar_t__) ; 
 int /*<<< orphan*/ * sk_ASN1_OBJECT_value (scalar_t__,int) ; 
 int trust_compat (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

__attribute__((used)) static int obj_trust(int id, X509 *x, int flags)
{
    X509_CERT_AUX *ax = x->aux;
    int i;

    if (ax && ax->reject) {
        for (i = 0; i < sk_ASN1_OBJECT_num(ax->reject); i++) {
            ASN1_OBJECT *obj = sk_ASN1_OBJECT_value(ax->reject, i);
            int nid = OBJ_obj2nid(obj);

            if (nid == id || (nid == NID_anyExtendedKeyUsage &&
                (flags & X509_TRUST_OK_ANY_EKU)))
                return X509_TRUST_REJECTED;
        }
    }

    if (ax && ax->trust) {
        for (i = 0; i < sk_ASN1_OBJECT_num(ax->trust); i++) {
            ASN1_OBJECT *obj = sk_ASN1_OBJECT_value(ax->trust, i);
            int nid = OBJ_obj2nid(obj);

            if (nid == id || (nid == NID_anyExtendedKeyUsage &&
                (flags & X509_TRUST_OK_ANY_EKU)))
                return X509_TRUST_TRUSTED;
        }
        /*
         * Reject when explicit trust EKU are set and none match.
         *
         * Returning untrusted is enough for for full chains that end in
         * self-signed roots, because when explicit trust is specified it
         * suppresses the default blanket trust of self-signed objects.
         *
         * But for partial chains, this is not enough, because absent a similar
         * trust-self-signed policy, non matching EKUs are indistinguishable
         * from lack of EKU constraints.
         *
         * Therefore, failure to match any trusted purpose must trigger an
         * explicit reject.
         */
        return X509_TRUST_REJECTED;
    }

    if ((flags & X509_TRUST_DO_SS_COMPAT) == 0)
        return X509_TRUST_UNTRUSTED;

    /*
     * Not rejected, and there is no list of accepted uses, try compat.
     */
    return trust_compat(NULL, x, flags);
}