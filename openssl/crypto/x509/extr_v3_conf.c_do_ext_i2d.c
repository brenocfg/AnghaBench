#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_EXTENSION ;
struct TYPE_7__ {int (* i2d ) (void*,unsigned char**) ;scalar_t__ it; } ;
typedef  TYPE_1__ X509V3_EXT_METHOD ;
struct TYPE_8__ {unsigned char* data; int length; } ;
typedef  TYPE_2__ ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_ITEM_ptr (scalar_t__) ; 
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (TYPE_2__*) ; 
 TYPE_2__* ASN1_OCTET_STRING_new () ; 
 int ASN1_item_i2d (void*,unsigned char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  X509V3_F_DO_EXT_I2D ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_EXTENSION_create_by_NID (int /*<<< orphan*/ *,int,int,TYPE_2__*) ; 
 int stub1 (void*,unsigned char**) ; 
 int stub2 (void*,unsigned char**) ; 

__attribute__((used)) static X509_EXTENSION *do_ext_i2d(const X509V3_EXT_METHOD *method,
                                  int ext_nid, int crit, void *ext_struc)
{
    unsigned char *ext_der = NULL;
    int ext_len;
    ASN1_OCTET_STRING *ext_oct = NULL;
    X509_EXTENSION *ext;
    /* Convert internal representation to DER */
    if (method->it) {
        ext_der = NULL;
        ext_len =
            ASN1_item_i2d(ext_struc, &ext_der, ASN1_ITEM_ptr(method->it));
        if (ext_len < 0)
            goto merr;
    } else {
        unsigned char *p;

        ext_len = method->i2d(ext_struc, NULL);
        if ((ext_der = OPENSSL_malloc(ext_len)) == NULL)
            goto merr;
        p = ext_der;
        method->i2d(ext_struc, &p);
    }
    if ((ext_oct = ASN1_OCTET_STRING_new()) == NULL)
        goto merr;
    ext_oct->data = ext_der;
    ext_der = NULL;
    ext_oct->length = ext_len;

    ext = X509_EXTENSION_create_by_NID(NULL, ext_nid, crit, ext_oct);
    if (!ext)
        goto merr;
    ASN1_OCTET_STRING_free(ext_oct);

    return ext;

 merr:
    X509V3err(X509V3_F_DO_EXT_I2D, ERR_R_MALLOC_FAILURE);
    OPENSSL_free(ext_der);
    ASN1_OCTET_STRING_free(ext_oct);
    return NULL;

}