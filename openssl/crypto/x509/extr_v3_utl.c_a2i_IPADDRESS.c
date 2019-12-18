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
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_OCTET_STRING_new () ; 
 int /*<<< orphan*/  ASN1_OCTET_STRING_set (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int a2i_ipadd (unsigned char*,char const*) ; 

ASN1_OCTET_STRING *a2i_IPADDRESS(const char *ipasc)
{
    unsigned char ipout[16];
    ASN1_OCTET_STRING *ret;
    int iplen;

    /* If string contains a ':' assume IPv6 */

    iplen = a2i_ipadd(ipout, ipasc);

    if (!iplen)
        return NULL;

    ret = ASN1_OCTET_STRING_new();
    if (ret == NULL)
        return NULL;
    if (!ASN1_OCTET_STRING_set(ret, ipout, iplen)) {
        ASN1_OCTET_STRING_free(ret);
        return NULL;
    }
    return ret;
}