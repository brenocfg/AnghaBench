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
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 char* ASN1_tag2str (int) ; 
 int /*<<< orphan*/  BIO_indent (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,int) ; 
 int BIO_write (int /*<<< orphan*/ *,char const*,int) ; 
 int V_ASN1_APPLICATION ; 
 int V_ASN1_CONSTRUCTED ; 
 int V_ASN1_CONTEXT_SPECIFIC ; 
 int V_ASN1_PRIVATE ; 

__attribute__((used)) static int asn1_print_info(BIO *bp, int tag, int xclass, int constructed,
                           int indent)
{
    static const char fmt[] = "%-18s";
    char str[128];
    const char *p;

    if (constructed & V_ASN1_CONSTRUCTED)
        p = "cons: ";
    else
        p = "prim: ";
    if (BIO_write(bp, p, 6) < 6)
        goto err;
    BIO_indent(bp, indent, 128);

    p = str;
    if ((xclass & V_ASN1_PRIVATE) == V_ASN1_PRIVATE)
        BIO_snprintf(str, sizeof(str), "priv [ %d ] ", tag);
    else if ((xclass & V_ASN1_CONTEXT_SPECIFIC) == V_ASN1_CONTEXT_SPECIFIC)
        BIO_snprintf(str, sizeof(str), "cont [ %d ]", tag);
    else if ((xclass & V_ASN1_APPLICATION) == V_ASN1_APPLICATION)
        BIO_snprintf(str, sizeof(str), "appl [ %d ]", tag);
    else if (tag > 30)
        BIO_snprintf(str, sizeof(str), "<ASN1 %d>", tag);
    else
        p = ASN1_tag2str(tag);

    if (BIO_printf(bp, fmt, p) <= 0)
        goto err;
    return 1;
 err:
    return 0;
}