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
struct key_type {int /*<<< orphan*/  digest; int /*<<< orphan*/  cipher; } ;
struct key_ctx_bi {int dummy; } ;

/* Variables and functions */
 int KEY_DIRECTION_INVERSE ; 
 int KEY_DIRECTION_NORMAL ; 
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  crypto_read_openvpn_key (struct key_type*,struct key_ctx_bi*,char const*,char const*,int const,char*,char*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 struct key_type tls_crypt_kt () ; 

void
tls_crypt_init_key(struct key_ctx_bi *key, const char *key_file,
                   const char *key_inline, bool tls_server)
{
    const int key_direction = tls_server ?
                              KEY_DIRECTION_NORMAL : KEY_DIRECTION_INVERSE;
    struct key_type kt = tls_crypt_kt();
    if (!kt.cipher || !kt.digest)
    {
        msg(M_FATAL, "ERROR: --tls-crypt not supported");
    }
    crypto_read_openvpn_key(&kt, key, key_file, key_inline, key_direction,
                            "Control Channel Encryption", "tls-crypt");
}