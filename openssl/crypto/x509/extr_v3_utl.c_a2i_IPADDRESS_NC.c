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
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strdup (char const*) ; 
 int a2i_ipadd (unsigned char*,char*) ; 
 char* strchr (char const*,char) ; 

ASN1_OCTET_STRING *a2i_IPADDRESS_NC(const char *ipasc)
{
    ASN1_OCTET_STRING *ret = NULL;
    unsigned char ipout[32];
    char *iptmp = NULL, *p;
    int iplen1, iplen2;

    p = strchr(ipasc, '/');
    if (p == NULL)
        return NULL;
    iptmp = OPENSSL_strdup(ipasc);
    if (iptmp == NULL)
        return NULL;
    p = iptmp + (p - ipasc);
    *p++ = 0;

    iplen1 = a2i_ipadd(ipout, iptmp);

    if (!iplen1)
        goto err;

    iplen2 = a2i_ipadd(ipout + iplen1, p);

    OPENSSL_free(iptmp);
    iptmp = NULL;

    if (!iplen2 || (iplen1 != iplen2))
        goto err;

    ret = ASN1_OCTET_STRING_new();
    if (ret == NULL)
        goto err;
    if (!ASN1_OCTET_STRING_set(ret, ipout, iplen1 + iplen2))
        goto err;

    return ret;

 err:
    OPENSSL_free(iptmp);
    ASN1_OCTET_STRING_free(ret);
    return NULL;
}