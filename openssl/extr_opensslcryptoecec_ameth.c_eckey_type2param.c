#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char* data; int length; } ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  TYPE_1__ ASN1_STRING ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_ECKEY_TYPE2PARAM ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_new_by_curve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_GROUP_set_asn1_flag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_new () ; 
 scalar_t__ EC_KEY_set_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_R_DECODE_ERROR ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OBJ_obj2nid (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OPENSSL_EC_NAMED_CURVE ; 
 int V_ASN1_OBJECT ; 
 int V_ASN1_SEQUENCE ; 
 int /*<<< orphan*/ * d2i_ECParameters (int /*<<< orphan*/ *,unsigned char const**,int) ; 

__attribute__((used)) static EC_KEY *eckey_type2param(int ptype, const void *pval)
{
    EC_KEY *eckey = NULL;
    EC_GROUP *group = NULL;

    if (ptype == V_ASN1_SEQUENCE) {
        const ASN1_STRING *pstr = pval;
        const unsigned char *pm = pstr->data;
        int pmlen = pstr->length;

        if ((eckey = d2i_ECParameters(NULL, &pm, pmlen)) == NULL) {
            ECerr(EC_F_ECKEY_TYPE2PARAM, EC_R_DECODE_ERROR);
            goto ecerr;
        }
    } else if (ptype == V_ASN1_OBJECT) {
        const ASN1_OBJECT *poid = pval;

        /*
         * type == V_ASN1_OBJECT => the parameters are given by an asn1 OID
         */
        if ((eckey = EC_KEY_new()) == NULL) {
            ECerr(EC_F_ECKEY_TYPE2PARAM, ERR_R_MALLOC_FAILURE);
            goto ecerr;
        }
        group = EC_GROUP_new_by_curve_name(OBJ_obj2nid(poid));
        if (group == NULL)
            goto ecerr;
        EC_GROUP_set_asn1_flag(group, OPENSSL_EC_NAMED_CURVE);
        if (EC_KEY_set_group(eckey, group) == 0)
            goto ecerr;
        EC_GROUP_free(group);
    } else {
        ECerr(EC_F_ECKEY_TYPE2PARAM, EC_R_DECODE_ERROR);
        goto ecerr;
    }

    return eckey;

 ecerr:
    EC_KEY_free(eckey);
    EC_GROUP_free(group);
    return NULL;
}