#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  point_conversion_form_t ;
struct TYPE_6__ {long version; int /*<<< orphan*/ * cofactor; int /*<<< orphan*/ * order; int /*<<< orphan*/ * base; int /*<<< orphan*/  curve; int /*<<< orphan*/  fieldID; } ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  TYPE_1__ ECPARAMETERS ;
typedef  int /*<<< orphan*/  BIGNUM ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_OCTET_STRING_new () ; 
 int /*<<< orphan*/  ASN1_STRING_set0 (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 void* BN_to_ASN1_INTEGER (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECPARAMETERS_free (TYPE_1__*) ; 
 TYPE_1__* ECPARAMETERS_new () ; 
 int /*<<< orphan*/  EC_F_EC_GROUP_GET_ECPARAMETERS ; 
 int /*<<< orphan*/ * EC_GROUP_get0_cofactor (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EC_GROUP_get0_generator (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EC_GROUP_get0_order (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_GROUP_get_point_conversion_form (int /*<<< orphan*/  const*) ; 
 size_t EC_POINT_point2buf (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_R_UNDEFINED_GENERATOR ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_ASN1_LIB ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  ec_asn1_group2curve (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ec_asn1_group2fieldid (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

ECPARAMETERS *EC_GROUP_get_ecparameters(const EC_GROUP *group,
                                               ECPARAMETERS *params)
{
    size_t len = 0;
    ECPARAMETERS *ret = NULL;
    const BIGNUM *tmp;
    unsigned char *buffer = NULL;
    const EC_POINT *point = NULL;
    point_conversion_form_t form;
    ASN1_INTEGER *orig;

    if (params == NULL) {
        if ((ret = ECPARAMETERS_new()) == NULL) {
            ECerr(EC_F_EC_GROUP_GET_ECPARAMETERS, ERR_R_MALLOC_FAILURE);
            goto err;
        }
    } else
        ret = params;

    /* set the version (always one) */
    ret->version = (long)0x1;

    /* set the fieldID */
    if (!ec_asn1_group2fieldid(group, ret->fieldID)) {
        ECerr(EC_F_EC_GROUP_GET_ECPARAMETERS, ERR_R_EC_LIB);
        goto err;
    }

    /* set the curve */
    if (!ec_asn1_group2curve(group, ret->curve)) {
        ECerr(EC_F_EC_GROUP_GET_ECPARAMETERS, ERR_R_EC_LIB);
        goto err;
    }

    /* set the base point */
    if ((point = EC_GROUP_get0_generator(group)) == NULL) {
        ECerr(EC_F_EC_GROUP_GET_ECPARAMETERS, EC_R_UNDEFINED_GENERATOR);
        goto err;
    }

    form = EC_GROUP_get_point_conversion_form(group);

    len = EC_POINT_point2buf(group, point, form, &buffer, NULL);
    if (len == 0) {
        ECerr(EC_F_EC_GROUP_GET_ECPARAMETERS, ERR_R_EC_LIB);
        goto err;
    }
    if (ret->base == NULL && (ret->base = ASN1_OCTET_STRING_new()) == NULL) {
        OPENSSL_free(buffer);
        ECerr(EC_F_EC_GROUP_GET_ECPARAMETERS, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    ASN1_STRING_set0(ret->base, buffer, len);

    /* set the order */
    tmp = EC_GROUP_get0_order(group);
    if (tmp == NULL) {
        ECerr(EC_F_EC_GROUP_GET_ECPARAMETERS, ERR_R_EC_LIB);
        goto err;
    }
    ret->order = BN_to_ASN1_INTEGER(tmp, orig = ret->order);
    if (ret->order == NULL) {
        ret->order = orig;
        ECerr(EC_F_EC_GROUP_GET_ECPARAMETERS, ERR_R_ASN1_LIB);
        goto err;
    }

    /* set the cofactor (optional) */
    tmp = EC_GROUP_get0_cofactor(group);
    if (tmp != NULL) {
        ret->cofactor = BN_to_ASN1_INTEGER(tmp, orig = ret->cofactor);
        if (ret->cofactor == NULL) {
            ret->cofactor = orig;
            ECerr(EC_F_EC_GROUP_GET_ECPARAMETERS, ERR_R_ASN1_LIB);
            goto err;
        }
    }

    return ret;

 err:
    if (params == NULL)
        ECPARAMETERS_free(ret);
    return NULL;
}