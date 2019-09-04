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
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_PKEY_CTRL_SUPPORTS_MD_NID ; 
 int EVP_PKEY_get_default_digest_nid (int /*<<< orphan*/ *,int*) ; 
 int evp_pkey_asn1_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int EVP_PKEY_supports_digest_nid(EVP_PKEY *pkey, int nid)
{
    int rv, default_nid;

    rv = evp_pkey_asn1_ctrl(pkey, ASN1_PKEY_CTRL_SUPPORTS_MD_NID, nid, NULL);
    if (rv == -2) {
        /*
         * If there is a mandatory default digest and this isn't it, then
         * the answer is 'no'.
         */
        rv = EVP_PKEY_get_default_digest_nid(pkey, &default_nid);
        if (rv == 2)
            return (nid == default_nid);
        /* zero is an error from EVP_PKEY_get_default_digest_nid() */
        if (rv == 0)
            return -1;
    }
    return rv;
}