#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_EXTENSION ;
typedef  int /*<<< orphan*/  X509V3_CTX ;
struct TYPE_5__ {unsigned char* data; long length; } ;
typedef  TYPE_1__ ASN1_OCTET_STRING ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (TYPE_1__*) ; 
 TYPE_1__* ASN1_OCTET_STRING_new () ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char const*) ; 
 int /*<<< orphan*/ * OBJ_txt2obj (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_hexstr2buf (char const*,long*) ; 
 int /*<<< orphan*/  X509V3_F_V3_GENERIC_EXTENSION ; 
 int /*<<< orphan*/  X509V3_R_EXTENSION_NAME_ERROR ; 
 int /*<<< orphan*/  X509V3_R_EXTENSION_VALUE_ERROR ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_EXTENSION_create_by_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 unsigned char* generic_asn1 (char const*,int /*<<< orphan*/ *,long*) ; 

__attribute__((used)) static X509_EXTENSION *v3_generic_extension(const char *ext, const char *value,
                                            int crit, int gen_type,
                                            X509V3_CTX *ctx)
{
    unsigned char *ext_der = NULL;
    long ext_len = 0;
    ASN1_OBJECT *obj = NULL;
    ASN1_OCTET_STRING *oct = NULL;
    X509_EXTENSION *extension = NULL;

    if ((obj = OBJ_txt2obj(ext, 0)) == NULL) {
        X509V3err(X509V3_F_V3_GENERIC_EXTENSION,
                  X509V3_R_EXTENSION_NAME_ERROR);
        ERR_add_error_data(2, "name=", ext);
        goto err;
    }

    if (gen_type == 1)
        ext_der = OPENSSL_hexstr2buf(value, &ext_len);
    else if (gen_type == 2)
        ext_der = generic_asn1(value, ctx, &ext_len);

    if (ext_der == NULL) {
        X509V3err(X509V3_F_V3_GENERIC_EXTENSION,
                  X509V3_R_EXTENSION_VALUE_ERROR);
        ERR_add_error_data(2, "value=", value);
        goto err;
    }

    if ((oct = ASN1_OCTET_STRING_new()) == NULL) {
        X509V3err(X509V3_F_V3_GENERIC_EXTENSION, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    oct->data = ext_der;
    oct->length = ext_len;
    ext_der = NULL;

    extension = X509_EXTENSION_create_by_OBJ(NULL, obj, crit, oct);

 err:
    ASN1_OBJECT_free(obj);
    ASN1_OCTET_STRING_free(oct);
    OPENSSL_free(ext_der);
    return extension;

}