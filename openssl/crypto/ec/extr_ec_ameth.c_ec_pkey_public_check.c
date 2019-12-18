#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ec; } ;
struct TYPE_5__ {TYPE_1__ pkey; } ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int EC_KEY_check_key (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ec_pkey_public_check(const EVP_PKEY *pkey)
{
    EC_KEY *eckey = pkey->pkey.ec;

    /*
     * Note: it unnecessary to check eckey->pub_key here since
     * it will be checked in EC_KEY_check_key(). In fact, the
     * EC_KEY_check_key() mainly checks the public key, and checks
     * the private key optionally (only if there is one). So if
     * someone passes a whole EC key (public + private), this
     * will also work...
     */

    return EC_KEY_check_key(eckey);
}