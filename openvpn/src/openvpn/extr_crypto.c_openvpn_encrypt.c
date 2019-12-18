#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cipher; } ;
struct TYPE_4__ {TYPE_1__ encrypt; } ;
struct crypto_options {TYPE_2__ key_ctx_bi; } ;
struct buffer {scalar_t__ len; } ;
typedef  int /*<<< orphan*/  cipher_kt_t ;

/* Variables and functions */
 int /*<<< orphan*/ * cipher_ctx_get_cipher_kt (int /*<<< orphan*/ ) ; 
 scalar_t__ cipher_kt_mode_aead (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  openvpn_encrypt_aead (struct buffer*,struct buffer,struct crypto_options*) ; 
 int /*<<< orphan*/  openvpn_encrypt_v1 (struct buffer*,struct buffer,struct crypto_options*) ; 

void
openvpn_encrypt(struct buffer *buf, struct buffer work,
                struct crypto_options *opt)
{
    if (buf->len > 0 && opt)
    {
        const cipher_kt_t *cipher_kt =
            cipher_ctx_get_cipher_kt(opt->key_ctx_bi.encrypt.cipher);

        if (cipher_kt_mode_aead(cipher_kt))
        {
            openvpn_encrypt_aead(buf, work, opt);
        }
        else
        {
            openvpn_encrypt_v1(buf, work, opt);
        }
    }
}