#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int exp_len; int exp_tag; int exp_constructed; int exp_class; scalar_t__ exp_pad; } ;
typedef  TYPE_1__ tag_exp_type ;
struct TYPE_5__ {int imp_tag; int imp_class; int exp_count; int utype; TYPE_1__* exp_list; int /*<<< orphan*/  format; int /*<<< orphan*/  str; } ;
typedef  TYPE_2__ tag_exp_arg ;
typedef  int /*<<< orphan*/  X509V3_CTX ;
typedef  int /*<<< orphan*/  ASN1_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_GEN_FORMAT_ASCII ; 
 int ASN1_GEN_SEQ_MAX_DEPTH ; 
 int ASN1_R_ILLEGAL_NESTED_TAGGING ; 
 int ASN1_R_SEQUENCE_OR_SET_NEEDS_CONFIG ; 
 int ASN1_R_UNKNOWN_TAG ; 
 int /*<<< orphan*/  ASN1_TYPE_free (int /*<<< orphan*/ *) ; 
 int ASN1_get_object (unsigned char const**,long*,int*,int*,int) ; 
 int ASN1_object_size (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ASN1_put_object (unsigned char**,int,long,int,int) ; 
 scalar_t__ CONF_parse_list (char const*,char,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int V_ASN1_CONSTRUCTED ; 
 int V_ASN1_SEQUENCE ; 
 int V_ASN1_SET ; 
 int V_ASN1_UNIVERSAL ; 
 int /*<<< orphan*/  asn1_cb ; 
 int /*<<< orphan*/ * asn1_multi (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/ * asn1_str2type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * d2i_ASN1_TYPE (int /*<<< orphan*/ *,unsigned char const**,int) ; 
 int i2d_ASN1_TYPE (int /*<<< orphan*/ *,unsigned char**) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 

__attribute__((used)) static ASN1_TYPE *generate_v3(const char *str, X509V3_CTX *cnf, int depth,
                              int *perr)
{
    ASN1_TYPE *ret;
    tag_exp_arg asn1_tags;
    tag_exp_type *etmp;

    int i, len;

    unsigned char *orig_der = NULL, *new_der = NULL;
    const unsigned char *cpy_start;
    unsigned char *p;
    const unsigned char *cp;
    int cpy_len;
    long hdr_len = 0;
    int hdr_constructed = 0, hdr_tag, hdr_class;
    int r;

    asn1_tags.imp_tag = -1;
    asn1_tags.imp_class = -1;
    asn1_tags.format = ASN1_GEN_FORMAT_ASCII;
    asn1_tags.exp_count = 0;
    if (CONF_parse_list(str, ',', 1, asn1_cb, &asn1_tags) != 0) {
        *perr = ASN1_R_UNKNOWN_TAG;
        return NULL;
    }

    if ((asn1_tags.utype == V_ASN1_SEQUENCE)
        || (asn1_tags.utype == V_ASN1_SET)) {
        if (!cnf) {
            *perr = ASN1_R_SEQUENCE_OR_SET_NEEDS_CONFIG;
            return NULL;
        }
        if (depth >= ASN1_GEN_SEQ_MAX_DEPTH) {
            *perr = ASN1_R_ILLEGAL_NESTED_TAGGING;
            return NULL;
        }
        ret = asn1_multi(asn1_tags.utype, asn1_tags.str, cnf, depth, perr);
    } else
        ret = asn1_str2type(asn1_tags.str, asn1_tags.format, asn1_tags.utype);

    if (!ret)
        return NULL;

    /* If no tagging return base type */
    if ((asn1_tags.imp_tag == -1) && (asn1_tags.exp_count == 0))
        return ret;

    /* Generate the encoding */
    cpy_len = i2d_ASN1_TYPE(ret, &orig_der);
    ASN1_TYPE_free(ret);
    ret = NULL;
    /* Set point to start copying for modified encoding */
    cpy_start = orig_der;

    /* Do we need IMPLICIT tagging? */
    if (asn1_tags.imp_tag != -1) {
        /* If IMPLICIT we will replace the underlying tag */
        /* Skip existing tag+len */
        r = ASN1_get_object(&cpy_start, &hdr_len, &hdr_tag, &hdr_class,
                            cpy_len);
        if (r & 0x80)
            goto err;
        /* Update copy length */
        cpy_len -= cpy_start - orig_der;
        /*
         * For IMPLICIT tagging the length should match the original length
         * and constructed flag should be consistent.
         */
        if (r & 0x1) {
            /* Indefinite length constructed */
            hdr_constructed = 2;
            hdr_len = 0;
        } else
            /* Just retain constructed flag */
            hdr_constructed = r & V_ASN1_CONSTRUCTED;
        /*
         * Work out new length with IMPLICIT tag: ignore constructed because
         * it will mess up if indefinite length
         */
        len = ASN1_object_size(0, hdr_len, asn1_tags.imp_tag);
    } else
        len = cpy_len;

    /* Work out length in any EXPLICIT, starting from end */

    for (i = 0, etmp = asn1_tags.exp_list + asn1_tags.exp_count - 1;
         i < asn1_tags.exp_count; i++, etmp--) {
        /* Content length: number of content octets + any padding */
        len += etmp->exp_pad;
        etmp->exp_len = len;
        /* Total object length: length including new header */
        len = ASN1_object_size(0, len, etmp->exp_tag);
    }

    /* Allocate buffer for new encoding */

    new_der = OPENSSL_malloc(len);
    if (new_der == NULL)
        goto err;

    /* Generate tagged encoding */

    p = new_der;

    /* Output explicit tags first */

    for (i = 0, etmp = asn1_tags.exp_list; i < asn1_tags.exp_count;
         i++, etmp++) {
        ASN1_put_object(&p, etmp->exp_constructed, etmp->exp_len,
                        etmp->exp_tag, etmp->exp_class);
        if (etmp->exp_pad)
            *p++ = 0;
    }

    /* If IMPLICIT, output tag */

    if (asn1_tags.imp_tag != -1) {
        if (asn1_tags.imp_class == V_ASN1_UNIVERSAL
            && (asn1_tags.imp_tag == V_ASN1_SEQUENCE
                || asn1_tags.imp_tag == V_ASN1_SET))
            hdr_constructed = V_ASN1_CONSTRUCTED;
        ASN1_put_object(&p, hdr_constructed, hdr_len,
                        asn1_tags.imp_tag, asn1_tags.imp_class);
    }

    /* Copy across original encoding */
    memcpy(p, cpy_start, cpy_len);

    cp = new_der;

    /* Obtain new ASN1_TYPE structure */
    ret = d2i_ASN1_TYPE(NULL, &cp, len);

 err:
    OPENSSL_free(orig_der);
    OPENSSL_free(new_der);

    return ret;

}