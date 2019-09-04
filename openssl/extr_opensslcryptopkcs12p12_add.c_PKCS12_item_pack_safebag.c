#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  octet; } ;
struct TYPE_12__ {TYPE_2__ value; void* type; } ;
struct TYPE_9__ {TYPE_4__* bag; } ;
struct TYPE_11__ {void* type; TYPE_1__ value; } ;
typedef  TYPE_3__ PKCS12_SAFEBAG ;
typedef  TYPE_4__ PKCS12_BAGS ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_item_pack (void*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 void* OBJ_nid2obj (int) ; 
 int /*<<< orphan*/  PKCS12_BAGS_free (TYPE_4__*) ; 
 TYPE_4__* PKCS12_BAGS_new () ; 
 int /*<<< orphan*/  PKCS12_F_PKCS12_ITEM_PACK_SAFEBAG ; 
 TYPE_3__* PKCS12_SAFEBAG_new () ; 
 int /*<<< orphan*/  PKCS12err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

PKCS12_SAFEBAG *PKCS12_item_pack_safebag(void *obj, const ASN1_ITEM *it,
                                         int nid1, int nid2)
{
    PKCS12_BAGS *bag;
    PKCS12_SAFEBAG *safebag;

    if ((bag = PKCS12_BAGS_new()) == NULL) {
        PKCS12err(PKCS12_F_PKCS12_ITEM_PACK_SAFEBAG, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    bag->type = OBJ_nid2obj(nid1);
    if (!ASN1_item_pack(obj, it, &bag->value.octet)) {
        PKCS12err(PKCS12_F_PKCS12_ITEM_PACK_SAFEBAG, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    if ((safebag = PKCS12_SAFEBAG_new()) == NULL) {
        PKCS12err(PKCS12_F_PKCS12_ITEM_PACK_SAFEBAG, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    safebag->value.bag = bag;
    safebag->type = OBJ_nid2obj(nid2);
    return safebag;

 err:
    PKCS12_BAGS_free(bag);
    return NULL;
}