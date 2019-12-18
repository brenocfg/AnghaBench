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

/* Variables and functions */
 int ASN1_get_object (unsigned char const**,long*,int*,int*,long) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int V_ASN1_APPLICATION ; 
 int V_ASN1_CONSTRUCTED ; 
 int V_ASN1_ENUMERATED ; 
 int V_ASN1_INTEGER ; 
 int V_ASN1_SEQUENCE ; 
 int V_ASN1_UNIVERSAL ; 
 int /*<<< orphan*/  bio_err ; 

__attribute__((used)) static int ldap_ExtendedResponse_parse(const char *buf, long rem)
{
    const unsigned char *cur, *end;
    long len;
    int tag, xclass, inf, ret = -1;

    cur = (const unsigned char *)buf;
    end = cur + rem;

    /*
     * From RFC 4511:
     *
     *    LDAPMessage ::= SEQUENCE {
     *         messageID       MessageID,
     *         protocolOp      CHOICE {
     *              ...
     *              extendedResp          ExtendedResponse,
     *              ... },
     *         controls       [0] Controls OPTIONAL }
     *
     *    ExtendedResponse ::= [APPLICATION 24] SEQUENCE {
     *         COMPONENTS OF LDAPResult,
     *         responseName     [10] LDAPOID OPTIONAL,
     *         responseValue    [11] OCTET STRING OPTIONAL }
     *
     *    LDAPResult ::= SEQUENCE {
     *         resultCode         ENUMERATED {
     *              success                      (0),
     *              ...
     *              other                        (80),
     *              ...  },
     *         matchedDN          LDAPDN,
     *         diagnosticMessage  LDAPString,
     *         referral           [3] Referral OPTIONAL }
     */

    /* pull SEQUENCE */
    inf = ASN1_get_object(&cur, &len, &tag, &xclass, rem);
    if (inf != V_ASN1_CONSTRUCTED || tag != V_ASN1_SEQUENCE ||
        (rem = end - cur, len > rem)) {
        BIO_printf(bio_err, "Unexpected LDAP response\n");
        goto end;
    }

    rem = len;  /* ensure that we don't overstep the SEQUENCE */

    /* pull MessageID */
    inf = ASN1_get_object(&cur, &len, &tag, &xclass, rem);
    if (inf != V_ASN1_UNIVERSAL || tag != V_ASN1_INTEGER ||
        (rem = end - cur, len > rem)) {
        BIO_printf(bio_err, "No MessageID\n");
        goto end;
    }

    cur += len; /* shall we check for MessageId match or just skip? */

    /* pull [APPLICATION 24] */
    rem = end - cur;
    inf = ASN1_get_object(&cur, &len, &tag, &xclass, rem);
    if (inf != V_ASN1_CONSTRUCTED || xclass != V_ASN1_APPLICATION ||
        tag != 24) {
        BIO_printf(bio_err, "Not ExtendedResponse\n");
        goto end;
    }

    /* pull resultCode */
    rem = end - cur;
    inf = ASN1_get_object(&cur, &len, &tag, &xclass, rem);
    if (inf != V_ASN1_UNIVERSAL || tag != V_ASN1_ENUMERATED || len == 0 ||
        (rem = end - cur, len > rem)) {
        BIO_printf(bio_err, "Not LDAPResult\n");
        goto end;
    }

    /* len should always be one, but just in case... */
    for (ret = 0, inf = 0; inf < len; inf++) {
        ret <<= 8;
        ret |= cur[inf];
    }
    /* There is more data, but we don't care... */
 end:
    return ret;
}