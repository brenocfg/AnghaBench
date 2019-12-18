#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ reason; int /*<<< orphan*/  serialNumber; } ;
typedef  TYPE_2__ X509_REVOKED ;
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_10__ {int /*<<< orphan*/ * revoked; } ;
struct TYPE_12__ {TYPE_1__ crl; int /*<<< orphan*/  lock; } ;
typedef  TYPE_3__ X509_CRL ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 scalar_t__ ASN1_INTEGER_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CRL_REASON_REMOVE_FROM_CRL ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ crl_revoked_issuer_match (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int sk_X509_REVOKED_find (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  sk_X509_REVOKED_is_sorted (int /*<<< orphan*/ *) ; 
 int sk_X509_REVOKED_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_X509_REVOKED_sort (int /*<<< orphan*/ *) ; 
 TYPE_2__* sk_X509_REVOKED_value (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int def_crl_lookup(X509_CRL *crl,
                          X509_REVOKED **ret, ASN1_INTEGER *serial,
                          X509_NAME *issuer)
{
    X509_REVOKED rtmp, *rev;
    int idx, num;

    if (crl->crl.revoked == NULL)
        return 0;

    /*
     * Sort revoked into serial number order if not already sorted. Do this
     * under a lock to avoid race condition.
     */
    if (!sk_X509_REVOKED_is_sorted(crl->crl.revoked)) {
        CRYPTO_THREAD_write_lock(crl->lock);
        sk_X509_REVOKED_sort(crl->crl.revoked);
        CRYPTO_THREAD_unlock(crl->lock);
    }
    rtmp.serialNumber = *serial;
    idx = sk_X509_REVOKED_find(crl->crl.revoked, &rtmp);
    if (idx < 0)
        return 0;
    /* Need to look for matching name */
    for (num = sk_X509_REVOKED_num(crl->crl.revoked); idx < num; idx++) {
        rev = sk_X509_REVOKED_value(crl->crl.revoked, idx);
        if (ASN1_INTEGER_cmp(&rev->serialNumber, serial))
            return 0;
        if (crl_revoked_issuer_match(crl, issuer, rev)) {
            if (ret)
                *ret = rev;
            if (rev->reason == CRL_REASON_REMOVE_FROM_CRL)
                return 2;
            return 1;
        }
    }
    return 0;
}