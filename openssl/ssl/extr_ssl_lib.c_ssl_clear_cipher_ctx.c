#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * compress; int /*<<< orphan*/ * expand; int /*<<< orphan*/ * enc_write_ctx; int /*<<< orphan*/ * enc_read_ctx; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 

void ssl_clear_cipher_ctx(SSL *s)
{
    if (s->enc_read_ctx != NULL) {
        EVP_CIPHER_CTX_free(s->enc_read_ctx);
        s->enc_read_ctx = NULL;
    }
    if (s->enc_write_ctx != NULL) {
        EVP_CIPHER_CTX_free(s->enc_write_ctx);
        s->enc_write_ctx = NULL;
    }
#ifndef OPENSSL_NO_COMP
    COMP_CTX_free(s->expand);
    s->expand = NULL;
    COMP_CTX_free(s->compress);
    s->compress = NULL;
#endif
}