#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* ameth; } ;
struct TYPE_6__ {int (* old_priv_encode ) (TYPE_2__ const*,unsigned char**) ;scalar_t__ priv_encode; } ;
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  TYPE_2__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_I2D_PRIVATEKEY ; 
 int /*<<< orphan*/  ASN1_R_UNSUPPORTED_PUBLIC_KEY_TYPE ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_PKEY2PKCS8 (TYPE_2__ const*) ; 
 int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO_free (int /*<<< orphan*/ *) ; 
 int i2d_PKCS8_PRIV_KEY_INFO (int /*<<< orphan*/ *,unsigned char**) ; 
 int stub1 (TYPE_2__ const*,unsigned char**) ; 

int i2d_PrivateKey(const EVP_PKEY *a, unsigned char **pp)
{
    if (a->ameth && a->ameth->old_priv_encode) {
        return a->ameth->old_priv_encode(a, pp);
    }
    if (a->ameth && a->ameth->priv_encode) {
        PKCS8_PRIV_KEY_INFO *p8 = EVP_PKEY2PKCS8(a);
        int ret = 0;
        if (p8 != NULL) {
            ret = i2d_PKCS8_PRIV_KEY_INFO(p8, pp);
            PKCS8_PRIV_KEY_INFO_free(p8);
        }
        return ret;
    }
    ASN1err(ASN1_F_I2D_PRIVATEKEY, ASN1_R_UNSUPPORTED_PUBLIC_KEY_TYPE);
    return -1;
}