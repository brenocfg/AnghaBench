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
typedef  int /*<<< orphan*/  PKCS7_SIGNER_INFO ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_OCTET_STRING_new () ; 
 int /*<<< orphan*/  ASN1_STRING_set (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  NID_pkcs9_messageDigest ; 
 int /*<<< orphan*/  PKCS7_add_signed_attribute (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_ASN1_OCTET_STRING ; 

int PKCS7_add1_attrib_digest(PKCS7_SIGNER_INFO *si,
                             const unsigned char *md, int mdlen)
{
    ASN1_OCTET_STRING *os;
    os = ASN1_OCTET_STRING_new();
    if (os == NULL)
        return 0;
    if (!ASN1_STRING_set(os, md, mdlen)
        || !PKCS7_add_signed_attribute(si, NID_pkcs9_messageDigest,
                                       V_ASN1_OCTET_STRING, os)) {
        ASN1_OCTET_STRING_free(os);
        return 0;
    }
    return 1;
}