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
struct TYPE_6__ {int /*<<< orphan*/  prime_infos; int /*<<< orphan*/  _method_mod_q; int /*<<< orphan*/  _method_mod_p; int /*<<< orphan*/  _method_mod_n; } ;
struct TYPE_5__ {int /*<<< orphan*/  m; } ;
typedef  TYPE_1__ RSA_PRIME_INFO ;
typedef  TYPE_2__ RSA ;

/* Variables and functions */
 int /*<<< orphan*/  BN_MONT_CTX_free (int /*<<< orphan*/ ) ; 
 int sk_RSA_PRIME_INFO_num (int /*<<< orphan*/ ) ; 
 TYPE_1__* sk_RSA_PRIME_INFO_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rsa_ossl_finish(RSA *rsa)
{
    int i;
    RSA_PRIME_INFO *pinfo;

    BN_MONT_CTX_free(rsa->_method_mod_n);
    BN_MONT_CTX_free(rsa->_method_mod_p);
    BN_MONT_CTX_free(rsa->_method_mod_q);
    for (i = 0; i < sk_RSA_PRIME_INFO_num(rsa->prime_infos); i++) {
        pinfo = sk_RSA_PRIME_INFO_value(rsa->prime_infos, i);
        BN_MONT_CTX_free(pinfo->m);
    }
    return 1;
}