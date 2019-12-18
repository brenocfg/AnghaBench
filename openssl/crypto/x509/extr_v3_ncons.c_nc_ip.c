#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* data; int length; } ;
typedef  TYPE_1__ ASN1_OCTET_STRING ;

/* Variables and functions */
 int X509_V_ERR_PERMITTED_VIOLATION ; 
 int X509_V_ERR_UNSUPPORTED_NAME_SYNTAX ; 
 int X509_V_OK ; 

__attribute__((used)) static int nc_ip(ASN1_OCTET_STRING *ip, ASN1_OCTET_STRING *base)
{
    int hostlen, baselen, i;
    unsigned char *hostptr, *baseptr, *maskptr;
    hostptr = ip->data;
    hostlen = ip->length;
    baseptr = base->data;
    baselen = base->length;

    /* Invalid if not IPv4 or IPv6 */
    if (!((hostlen == 4) || (hostlen == 16)))
        return X509_V_ERR_UNSUPPORTED_NAME_SYNTAX;
    if (!((baselen == 8) || (baselen == 32)))
        return X509_V_ERR_UNSUPPORTED_NAME_SYNTAX;

    /* Do not match IPv4 with IPv6 */
    if (hostlen * 2 != baselen)
        return X509_V_ERR_PERMITTED_VIOLATION;

    maskptr = base->data + hostlen;

    /* Considering possible not aligned base ipAddress */
    /* Not checking for wrong mask definition: i.e.: 255.0.255.0 */
    for (i = 0; i < hostlen; i++)
        if ((hostptr[i] & maskptr[i]) != (baseptr[i] & maskptr[i]))
            return X509_V_ERR_PERMITTED_VIOLATION;

    return X509_V_OK;

}