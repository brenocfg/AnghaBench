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
 unsigned int ENGINE_METHOD_CIPHERS ; 
 unsigned int ENGINE_METHOD_DH ; 
 unsigned int ENGINE_METHOD_DIGESTS ; 
 unsigned int ENGINE_METHOD_DSA ; 
 unsigned int ENGINE_METHOD_EC ; 
 unsigned int ENGINE_METHOD_PKEY_ASN1_METHS ; 
 unsigned int ENGINE_METHOD_PKEY_METHS ; 
 unsigned int ENGINE_METHOD_RAND ; 
 unsigned int ENGINE_METHOD_RSA ; 
 int /*<<< orphan*/  ENGINE_set_default_DH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_set_default_DSA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_set_default_EC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_set_default_RAND (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_set_default_RSA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_set_default_ciphers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_set_default_digests (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_set_default_pkey_asn1_meths (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_set_default_pkey_meths (int /*<<< orphan*/ *) ; 

int ENGINE_set_default(ENGINE *e, unsigned int flags)
{
    if ((flags & ENGINE_METHOD_CIPHERS) && !ENGINE_set_default_ciphers(e))
        return 0;
    if ((flags & ENGINE_METHOD_DIGESTS) && !ENGINE_set_default_digests(e))
        return 0;
#ifndef OPENSSL_NO_RSA
    if ((flags & ENGINE_METHOD_RSA) && !ENGINE_set_default_RSA(e))
        return 0;
#endif
#ifndef OPENSSL_NO_DSA
    if ((flags & ENGINE_METHOD_DSA) && !ENGINE_set_default_DSA(e))
        return 0;
#endif
#ifndef OPENSSL_NO_DH
    if ((flags & ENGINE_METHOD_DH) && !ENGINE_set_default_DH(e))
        return 0;
#endif
#ifndef OPENSSL_NO_EC
    if ((flags & ENGINE_METHOD_EC) && !ENGINE_set_default_EC(e))
        return 0;
#endif
    if ((flags & ENGINE_METHOD_RAND) && !ENGINE_set_default_RAND(e))
        return 0;
    if ((flags & ENGINE_METHOD_PKEY_METHS)
        && !ENGINE_set_default_pkey_meths(e))
        return 0;
    if ((flags & ENGINE_METHOD_PKEY_ASN1_METHS)
        && !ENGINE_set_default_pkey_asn1_meths(e))
        return 0;
    return 1;
}