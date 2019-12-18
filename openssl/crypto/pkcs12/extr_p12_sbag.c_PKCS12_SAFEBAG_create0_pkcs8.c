#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_SIG ;
struct TYPE_5__ {int /*<<< orphan*/ * shkeybag; } ;
struct TYPE_6__ {TYPE_1__ value; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ PKCS12_SAFEBAG ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  NID_pkcs8ShroudedKeyBag ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKCS12_F_PKCS12_SAFEBAG_CREATE0_PKCS8 ; 
 TYPE_2__* PKCS12_SAFEBAG_new () ; 
 int /*<<< orphan*/  PKCS12err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

PKCS12_SAFEBAG *PKCS12_SAFEBAG_create0_pkcs8(X509_SIG *p8)
{
    PKCS12_SAFEBAG *bag = PKCS12_SAFEBAG_new();

    /* Set up the safe bag */
    if (bag == NULL) {
        PKCS12err(PKCS12_F_PKCS12_SAFEBAG_CREATE0_PKCS8, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    bag->type = OBJ_nid2obj(NID_pkcs8ShroudedKeyBag);
    bag->value.shkeybag = p8;
    return bag;
}