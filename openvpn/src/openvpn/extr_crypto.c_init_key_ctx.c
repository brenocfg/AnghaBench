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
struct key_type {int cipher_length; int hmac_length; scalar_t__ digest; scalar_t__ cipher; } ;
struct key_ctx {int /*<<< orphan*/  hmac; int /*<<< orphan*/  cipher; } ;
struct key {int /*<<< orphan*/  hmac; int /*<<< orphan*/  cipher; } ;
struct gc_arena {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct key_ctx) ; 
 int /*<<< orphan*/  D_CRYPTO_DEBUG ; 
 int /*<<< orphan*/  D_HANDSHAKE ; 
 int /*<<< orphan*/  D_SHOW_KEYS ; 
 int /*<<< orphan*/  M_WARN ; 
 int /*<<< orphan*/  cipher_ctx_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 int /*<<< orphan*/  cipher_ctx_new () ; 
 int cipher_kt_block_size (scalar_t__) ; 
 scalar_t__ cipher_kt_insecure (scalar_t__) ; 
 int /*<<< orphan*/  cipher_kt_iv_size (scalar_t__) ; 
 int /*<<< orphan*/  cipher_kt_name (scalar_t__) ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,char const*,int,...) ; 
 int /*<<< orphan*/  format_hex (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct gc_arena*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  hmac_ctx_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  hmac_ctx_new () ; 
 int /*<<< orphan*/  hmac_ctx_size (int /*<<< orphan*/ ) ; 
 int md_kt_name (scalar_t__) ; 
 int md_kt_size (scalar_t__) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 int translate_cipher_name_to_openvpn (int /*<<< orphan*/ ) ; 

void
init_key_ctx(struct key_ctx *ctx, const struct key *key,
             const struct key_type *kt, int enc,
             const char *prefix)
{
    struct gc_arena gc = gc_new();
    CLEAR(*ctx);
    if (kt->cipher && kt->cipher_length > 0)
    {

        ctx->cipher = cipher_ctx_new();
        cipher_ctx_init(ctx->cipher, key->cipher, kt->cipher_length,
                        kt->cipher, enc);

        msg(D_HANDSHAKE, "%s: Cipher '%s' initialized with %d bit key",
            prefix,
            translate_cipher_name_to_openvpn(cipher_kt_name(kt->cipher)),
            kt->cipher_length *8);

        dmsg(D_SHOW_KEYS, "%s: CIPHER KEY: %s", prefix,
             format_hex(key->cipher, kt->cipher_length, 0, &gc));
        dmsg(D_CRYPTO_DEBUG, "%s: CIPHER block_size=%d iv_size=%d",
             prefix, cipher_kt_block_size(kt->cipher),
             cipher_kt_iv_size(kt->cipher));
        if (cipher_kt_insecure(kt->cipher))
        {
            msg(M_WARN, "WARNING: INSECURE cipher with block size less than 128"
                " bit (%d bit).  This allows attacks like SWEET32.  Mitigate by "
                "using a --cipher with a larger block size (e.g. AES-256-CBC).",
                cipher_kt_block_size(kt->cipher)*8);
        }
    }
    if (kt->digest && kt->hmac_length > 0)
    {
        ctx->hmac = hmac_ctx_new();
        hmac_ctx_init(ctx->hmac, key->hmac, kt->hmac_length, kt->digest);

        msg(D_HANDSHAKE,
            "%s: Using %d bit message hash '%s' for HMAC authentication",
            prefix, md_kt_size(kt->digest) * 8, md_kt_name(kt->digest));

        dmsg(D_SHOW_KEYS, "%s: HMAC KEY: %s", prefix,
             format_hex(key->hmac, kt->hmac_length, 0, &gc));

        dmsg(D_CRYPTO_DEBUG, "%s: HMAC size=%d block_size=%d",
             prefix,
             md_kt_size(kt->digest),
             hmac_ctx_size(ctx->hmac));

    }
    gc_free(&gc);
}