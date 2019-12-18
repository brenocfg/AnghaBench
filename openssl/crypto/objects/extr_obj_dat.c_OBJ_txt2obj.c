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
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int ASN1_object_size (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_put_object (unsigned char**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int NID_undef ; 
 int /*<<< orphan*/  OBJ_F_OBJ_TXT2OBJ ; 
 int OBJ_ln2nid (char const*) ; 
 int /*<<< orphan*/ * OBJ_nid2obj (int) ; 
 int OBJ_sn2nid (char const*) ; 
 int /*<<< orphan*/  OBJerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  V_ASN1_OBJECT ; 
 int /*<<< orphan*/  V_ASN1_UNIVERSAL ; 
 int a2d_ASN1_OBJECT (unsigned char*,int,char const*,int) ; 
 int /*<<< orphan*/ * d2i_ASN1_OBJECT (int /*<<< orphan*/ *,unsigned char const**,int) ; 

ASN1_OBJECT *OBJ_txt2obj(const char *s, int no_name)
{
    int nid = NID_undef;
    ASN1_OBJECT *op;
    unsigned char *buf;
    unsigned char *p;
    const unsigned char *cp;
    int i, j;

    if (!no_name) {
        if (((nid = OBJ_sn2nid(s)) != NID_undef) ||
            ((nid = OBJ_ln2nid(s)) != NID_undef))
            return OBJ_nid2obj(nid);
    }

    /* Work out size of content octets */
    i = a2d_ASN1_OBJECT(NULL, 0, s, -1);
    if (i <= 0) {
        /* Don't clear the error */
        /*
         * ERR_clear_error();
         */
        return NULL;
    }
    /* Work out total size */
    j = ASN1_object_size(0, i, V_ASN1_OBJECT);
    if (j < 0)
        return NULL;

    if ((buf = OPENSSL_malloc(j)) == NULL) {
        OBJerr(OBJ_F_OBJ_TXT2OBJ, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    p = buf;
    /* Write out tag+length */
    ASN1_put_object(&p, 0, i, V_ASN1_OBJECT, V_ASN1_UNIVERSAL);
    /* Write out contents */
    a2d_ASN1_OBJECT(p, i, s, -1);

    cp = buf;
    op = d2i_ASN1_OBJECT(NULL, &cp, j);
    OPENSSL_free(buf);
    return op;
}