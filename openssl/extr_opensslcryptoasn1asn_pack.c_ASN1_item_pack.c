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
struct TYPE_6__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ ASN1_STRING ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_ITEM_PACK ; 
 int /*<<< orphan*/  ASN1_R_ENCODE_ERROR ; 
 int /*<<< orphan*/  ASN1_STRING_free (TYPE_1__*) ; 
 TYPE_1__* ASN1_STRING_new () ; 
 int /*<<< orphan*/  ASN1_item_i2d (void*,int /*<<< orphan*/ **,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 

ASN1_STRING *ASN1_item_pack(void *obj, const ASN1_ITEM *it, ASN1_STRING **oct)
{
    ASN1_STRING *octmp;

     if (oct == NULL || *oct == NULL) {
        if ((octmp = ASN1_STRING_new()) == NULL) {
            ASN1err(ASN1_F_ASN1_ITEM_PACK, ERR_R_MALLOC_FAILURE);
            return NULL;
        }
    } else {
        octmp = *oct;
    }

    OPENSSL_free(octmp->data);
    octmp->data = NULL;

    if ((octmp->length = ASN1_item_i2d(obj, &octmp->data, it)) == 0) {
        ASN1err(ASN1_F_ASN1_ITEM_PACK, ASN1_R_ENCODE_ERROR);
        goto err;
    }
    if (octmp->data == NULL) {
        ASN1err(ASN1_F_ASN1_ITEM_PACK, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (oct != NULL && *oct == NULL)
        *oct = octmp;

    return octmp;
 err:
    if (oct == NULL || *oct == NULL)
        ASN1_STRING_free(octmp);
    return NULL;
}