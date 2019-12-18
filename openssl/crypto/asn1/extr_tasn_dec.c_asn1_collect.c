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
typedef  int /*<<< orphan*/  BUF_MEM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_COLLECT ; 
 int ASN1_MAX_STRING_NEST ; 
 int /*<<< orphan*/  ASN1_R_MISSING_EOC ; 
 int /*<<< orphan*/  ASN1_R_NESTED_ASN1_STRING ; 
 int /*<<< orphan*/  ASN1_R_UNEXPECTED_EOC ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_NESTED_ASN1_ERROR ; 
 scalar_t__ asn1_check_eoc (unsigned char const**,long) ; 
 int /*<<< orphan*/  asn1_check_tlen (long*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,unsigned char const**,long,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  collect_data (int /*<<< orphan*/ *,unsigned char const**,long) ; 

__attribute__((used)) static int asn1_collect(BUF_MEM *buf, const unsigned char **in, long len,
                        char inf, int tag, int aclass, int depth)
{
    const unsigned char *p, *q;
    long plen;
    char cst, ininf;
    p = *in;
    inf &= 1;
    /*
     * If no buffer and not indefinite length constructed just pass over the
     * encoded data
     */
    if (!buf && !inf) {
        *in += len;
        return 1;
    }
    while (len > 0) {
        q = p;
        /* Check for EOC */
        if (asn1_check_eoc(&p, len)) {
            /*
             * EOC is illegal outside indefinite length constructed form
             */
            if (!inf) {
                ASN1err(ASN1_F_ASN1_COLLECT, ASN1_R_UNEXPECTED_EOC);
                return 0;
            }
            inf = 0;
            break;
        }

        if (!asn1_check_tlen(&plen, NULL, NULL, &ininf, &cst, &p,
                             len, tag, aclass, 0, NULL)) {
            ASN1err(ASN1_F_ASN1_COLLECT, ERR_R_NESTED_ASN1_ERROR);
            return 0;
        }

        /* If indefinite length constructed update max length */
        if (cst) {
            if (depth >= ASN1_MAX_STRING_NEST) {
                ASN1err(ASN1_F_ASN1_COLLECT, ASN1_R_NESTED_ASN1_STRING);
                return 0;
            }
            if (!asn1_collect(buf, &p, plen, ininf, tag, aclass, depth + 1))
                return 0;
        } else if (plen && !collect_data(buf, &p, plen))
            return 0;
        len -= p - q;
    }
    if (inf) {
        ASN1err(ASN1_F_ASN1_COLLECT, ASN1_R_MISSING_EOC);
        return 0;
    }
    *in = p;
    return 1;
}