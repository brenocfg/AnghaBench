#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash ;
struct TYPE_8__ {TYPE_1__* session; } ;
struct TYPE_7__ {int /*<<< orphan*/  master_key_length; int /*<<< orphan*/  master_key; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,size_t) ; 
 size_t TLS1_FINISH_MAC_LENGTH ; 
 int /*<<< orphan*/  ssl3_digest_cached_records (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_handshake_hash (TYPE_2__*,unsigned char*,int,size_t*) ; 
 int /*<<< orphan*/  tls1_PRF (TYPE_2__*,char const*,size_t,unsigned char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t,int) ; 

size_t tls1_final_finish_mac(SSL *s, const char *str, size_t slen,
                             unsigned char *out)
{
    size_t hashlen;
    unsigned char hash[EVP_MAX_MD_SIZE];

    if (!ssl3_digest_cached_records(s, 0)) {
        /* SSLfatal() already called */
        return 0;
    }

    if (!ssl_handshake_hash(s, hash, sizeof(hash), &hashlen)) {
        /* SSLfatal() already called */
        return 0;
    }

    if (!tls1_PRF(s, str, slen, hash, hashlen, NULL, 0, NULL, 0, NULL, 0,
                  s->session->master_key, s->session->master_key_length,
                  out, TLS1_FINISH_MAC_LENGTH, 1)) {
        /* SSLfatal() already called */
        return 0;
    }
    OPENSSL_cleanse(hash, hashlen);
    return TLS1_FINISH_MAC_LENGTH;
}