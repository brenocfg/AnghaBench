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
 scalar_t__ ENGINE_set_DH (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ENGINE_set_DSA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ENGINE_set_EC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ENGINE_set_RSA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ENGINE_set_ciphers (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_cmd_defns (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_ctrl_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_destroy_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ENGINE_set_digests (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devcrypto_ciphers ; 
 int /*<<< orphan*/  devcrypto_cmds ; 
 int /*<<< orphan*/  devcrypto_ctrl ; 
 int /*<<< orphan*/  devcrypto_dh ; 
 int /*<<< orphan*/  devcrypto_digests ; 
 int /*<<< orphan*/  devcrypto_dsa ; 
 int /*<<< orphan*/  devcrypto_ec ; 
 int /*<<< orphan*/  devcrypto_rsa ; 
 int /*<<< orphan*/  devcrypto_unload ; 
 int /*<<< orphan*/  engine_devcrypto_id ; 
 int /*<<< orphan*/  prepare_cipher_methods () ; 
 int /*<<< orphan*/  prepare_digest_methods () ; 

__attribute__((used)) static int bind_devcrypto(ENGINE *e) {

    if (!ENGINE_set_id(e, engine_devcrypto_id)
        || !ENGINE_set_name(e, "/dev/crypto engine")
        || !ENGINE_set_destroy_function(e, devcrypto_unload)
        || !ENGINE_set_cmd_defns(e, devcrypto_cmds)
        || !ENGINE_set_ctrl_function(e, devcrypto_ctrl))
        return 0;

    prepare_cipher_methods();
#ifdef IMPLEMENT_DIGEST
    prepare_digest_methods();
#endif

    return (ENGINE_set_ciphers(e, devcrypto_ciphers)
#ifdef IMPLEMENT_DIGEST
        && ENGINE_set_digests(e, devcrypto_digests)
#endif
/*
 * Asymmetric ciphers aren't well supported with /dev/crypto.  Among the BSD
 * implementations, it seems to only exist in FreeBSD, and regarding the
 * parameters in its crypt_kop, the manual crypto(4) has this to say:
 *
 *    The semantics of these arguments are currently undocumented.
 *
 * Reading through the FreeBSD source code doesn't give much more than
 * their CRK_MOD_EXP implementation for ubsec.
 *
 * It doesn't look much better with cryptodev-linux.  They have the crypt_kop
 * structure as well as the command (CRK_*) in cryptodev.h, but no support
 * seems to be implemented at all for the moment.
 *
 * At the time of writing, it seems impossible to write proper support for
 * FreeBSD's asym features without some very deep knowledge and access to
 * specific kernel modules.
 *
 * /Richard Levitte, 2017-05-11
 */
#if 0
# ifndef OPENSSL_NO_RSA
        && ENGINE_set_RSA(e, devcrypto_rsa)
# endif
# ifndef OPENSSL_NO_DSA
        && ENGINE_set_DSA(e, devcrypto_dsa)
# endif
# ifndef OPENSSL_NO_DH
        && ENGINE_set_DH(e, devcrypto_dh)
# endif
# ifndef OPENSSL_NO_EC
        && ENGINE_set_EC(e, devcrypto_ec)
# endif
#endif
        );
}