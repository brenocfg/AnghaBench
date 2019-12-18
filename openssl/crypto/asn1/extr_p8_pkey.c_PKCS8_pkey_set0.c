#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pkey; int /*<<< orphan*/  pkeyalg; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ PKCS8_PRIV_KEY_INFO ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ASN1_STRING_set0 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  X509_ALGOR_set0 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void*) ; 

int PKCS8_pkey_set0(PKCS8_PRIV_KEY_INFO *priv, ASN1_OBJECT *aobj,
                    int version,
                    int ptype, void *pval, unsigned char *penc, int penclen)
{
    if (version >= 0) {
        if (!ASN1_INTEGER_set(priv->version, version))
            return 0;
    }
    if (!X509_ALGOR_set0(priv->pkeyalg, aobj, ptype, pval))
        return 0;
    if (penc)
        ASN1_STRING_set0(priv->pkey, penc, penclen);
    return 1;
}