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
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_5__ {int /*<<< orphan*/ * shkeybag; } ;
struct TYPE_6__ {TYPE_1__ value; } ;
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  TYPE_2__ PKCS12_SAFEBAG ;

/* Variables and functions */
 scalar_t__ NID_pkcs8ShroudedKeyBag ; 
 scalar_t__ PKCS12_SAFEBAG_get_nid (TYPE_2__*) ; 
 int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PKCS8_decrypt (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/ * PKCS8_encrypt (int,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_SIG_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_SIG_get0 (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alg_get (int /*<<< orphan*/  const*,int*,int*,int*) ; 

__attribute__((used)) static int newpass_bag(PKCS12_SAFEBAG *bag, const char *oldpass,
                       const char *newpass)
{
    PKCS8_PRIV_KEY_INFO *p8;
    X509_SIG *p8new;
    int p8_nid, p8_saltlen, p8_iter;
    const X509_ALGOR *shalg;

    if (PKCS12_SAFEBAG_get_nid(bag) != NID_pkcs8ShroudedKeyBag)
        return 1;

    if ((p8 = PKCS8_decrypt(bag->value.shkeybag, oldpass, -1)) == NULL)
        return 0;
    X509_SIG_get0(bag->value.shkeybag, &shalg, NULL);
    if (!alg_get(shalg, &p8_nid, &p8_iter, &p8_saltlen))
        return 0;
    p8new = PKCS8_encrypt(p8_nid, NULL, newpass, -1, NULL, p8_saltlen,
                          p8_iter, p8);
    PKCS8_PRIV_KEY_INFO_free(p8);
    if (p8new == NULL)
        return 0;
    X509_SIG_free(bag->value.shkeybag);
    bag->value.shkeybag = p8new;
    return 1;
}