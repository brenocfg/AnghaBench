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
typedef  int /*<<< orphan*/  uint8_t ;
struct key_ctx {size_t implicit_iv_len; int /*<<< orphan*/  implicit_iv; int /*<<< orphan*/  cipher; } ;
typedef  int /*<<< orphan*/  packet_id_type ;
typedef  int /*<<< orphan*/  cipher_kt_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int OPENVPN_AEAD_MIN_IV_LEN ; 
 size_t OPENVPN_MAX_IV_LENGTH ; 
 int /*<<< orphan*/ * cipher_ctx_get_cipher_kt (int /*<<< orphan*/ ) ; 
 int cipher_kt_iv_size (int /*<<< orphan*/  const*) ; 
 scalar_t__ cipher_kt_mode_aead (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
key_ctx_update_implicit_iv(struct key_ctx *ctx, uint8_t *key, size_t key_len)
{
    const cipher_kt_t *cipher_kt = cipher_ctx_get_cipher_kt(ctx->cipher);

    /* Only use implicit IV in AEAD cipher mode, where HMAC key is not used */
    if (cipher_kt_mode_aead(cipher_kt))
    {
        size_t impl_iv_len = 0;
        ASSERT(cipher_kt_iv_size(cipher_kt) >= OPENVPN_AEAD_MIN_IV_LEN);
        impl_iv_len = cipher_kt_iv_size(cipher_kt) - sizeof(packet_id_type);
        ASSERT(impl_iv_len <= OPENVPN_MAX_IV_LENGTH);
        ASSERT(impl_iv_len <= key_len);
        memcpy(ctx->implicit_iv, key, impl_iv_len);
        ctx->implicit_iv_len = impl_iv_len;
    }
}