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
struct TYPE_4__ {int valid; int ret; long plen; int pclass; int ptag; int hdrlen; } ;
typedef  TYPE_1__ ASN1_TLC ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_CHECK_TLEN ; 
 int /*<<< orphan*/  ASN1_R_BAD_OBJECT_HEADER ; 
 int /*<<< orphan*/  ASN1_R_TOO_LONG ; 
 int /*<<< orphan*/  ASN1_R_WRONG_TAG ; 
 int ASN1_get_object (unsigned char const**,long*,int*,int*,long) ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int V_ASN1_CONSTRUCTED ; 
 int /*<<< orphan*/  asn1_tlc_clear (TYPE_1__*) ; 

__attribute__((used)) static int asn1_check_tlen(long *olen, int *otag, unsigned char *oclass,
                           char *inf, char *cst,
                           const unsigned char **in, long len,
                           int exptag, int expclass, char opt, ASN1_TLC *ctx)
{
    int i;
    int ptag, pclass;
    long plen;
    const unsigned char *p, *q;
    p = *in;
    q = p;

    if (ctx && ctx->valid) {
        i = ctx->ret;
        plen = ctx->plen;
        pclass = ctx->pclass;
        ptag = ctx->ptag;
        p += ctx->hdrlen;
    } else {
        i = ASN1_get_object(&p, &plen, &ptag, &pclass, len);
        if (ctx) {
            ctx->ret = i;
            ctx->plen = plen;
            ctx->pclass = pclass;
            ctx->ptag = ptag;
            ctx->hdrlen = p - q;
            ctx->valid = 1;
            /*
             * If definite length, and no error, length + header can't exceed
             * total amount of data available.
             */
            if (!(i & 0x81) && ((plen + ctx->hdrlen) > len)) {
                ASN1err(ASN1_F_ASN1_CHECK_TLEN, ASN1_R_TOO_LONG);
                asn1_tlc_clear(ctx);
                return 0;
            }
        }
    }

    if (i & 0x80) {
        ASN1err(ASN1_F_ASN1_CHECK_TLEN, ASN1_R_BAD_OBJECT_HEADER);
        asn1_tlc_clear(ctx);
        return 0;
    }
    if (exptag >= 0) {
        if ((exptag != ptag) || (expclass != pclass)) {
            /*
             * If type is OPTIONAL, not an error: indicate missing type.
             */
            if (opt)
                return -1;
            asn1_tlc_clear(ctx);
            ASN1err(ASN1_F_ASN1_CHECK_TLEN, ASN1_R_WRONG_TAG);
            return 0;
        }
        /*
         * We have a tag and class match: assume we are going to do something
         * with it
         */
        asn1_tlc_clear(ctx);
    }

    if (i & 1)
        plen = len - (p - q);

    if (inf)
        *inf = i & 1;

    if (cst)
        *cst = i & V_ASN1_CONSTRUCTED;

    if (olen)
        *olen = plen;

    if (oclass)
        *oclass = pclass;

    if (otag)
        *otag = ptag;

    *in = p;
    return 1;
}