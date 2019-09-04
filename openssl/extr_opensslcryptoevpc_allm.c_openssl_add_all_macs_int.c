#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  EVP_add_mac (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blake2b_mac_meth ; 
 int /*<<< orphan*/  blake2s_mac_meth ; 
 int /*<<< orphan*/  cmac_meth ; 
 int /*<<< orphan*/  gmac_meth ; 
 int /*<<< orphan*/  hmac_meth ; 
 int /*<<< orphan*/  kmac128_meth ; 
 int /*<<< orphan*/  kmac256_meth ; 
 int /*<<< orphan*/  poly1305_meth ; 
 int /*<<< orphan*/  siphash_meth ; 

void openssl_add_all_macs_int(void)
{
#ifndef OPENSSL_NO_BLAKE2
    EVP_add_mac(&blake2b_mac_meth);
    EVP_add_mac(&blake2s_mac_meth);
#endif
#ifndef OPENSSL_NO_CMAC
    EVP_add_mac(&cmac_meth);
#endif
    EVP_add_mac(&gmac_meth);
    EVP_add_mac(&hmac_meth);
    EVP_add_mac(&kmac128_meth);
    EVP_add_mac(&kmac256_meth);
#ifndef OPENSSL_NO_SIPHASH
    EVP_add_mac(&siphash_meth);
#endif
#ifndef OPENSSL_NO_POLY1305
    EVP_add_mac(&poly1305_meth);
#endif
}