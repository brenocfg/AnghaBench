#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* pkey; } ;
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ PKCS8_PRIV_KEY_INFO ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int ASN1_OP_FREE_PRE ; 
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pkey_cb(int operation, ASN1_VALUE **pval, const ASN1_ITEM *it,
                   void *exarg)
{
    /* Since the structure must still be valid use ASN1_OP_FREE_PRE */
    if (operation == ASN1_OP_FREE_PRE) {
        PKCS8_PRIV_KEY_INFO *key = (PKCS8_PRIV_KEY_INFO *)*pval;
        if (key->pkey)
            OPENSSL_cleanse(key->pkey->data, key->pkey->length);
    }
    return 1;
}