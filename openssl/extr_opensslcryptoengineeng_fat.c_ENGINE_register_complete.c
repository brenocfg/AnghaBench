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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_register_DH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_register_DSA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_register_EC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_register_RAND (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_register_RSA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_register_ciphers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_register_digests (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_register_pkey_asn1_meths (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_register_pkey_meths (int /*<<< orphan*/ *) ; 

int ENGINE_register_complete(ENGINE *e)
{
    ENGINE_register_ciphers(e);
    ENGINE_register_digests(e);
#ifndef OPENSSL_NO_RSA
    ENGINE_register_RSA(e);
#endif
#ifndef OPENSSL_NO_DSA
    ENGINE_register_DSA(e);
#endif
#ifndef OPENSSL_NO_DH
    ENGINE_register_DH(e);
#endif
#ifndef OPENSSL_NO_EC
    ENGINE_register_EC(e);
#endif
    ENGINE_register_RAND(e);
    ENGINE_register_pkey_meths(e);
    ENGINE_register_pkey_asn1_meths(e);
    return 1;
}