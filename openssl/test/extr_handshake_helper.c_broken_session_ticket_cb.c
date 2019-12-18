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
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  HMAC_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */

__attribute__((used)) static int broken_session_ticket_cb(SSL *s, unsigned char *key_name, unsigned char *iv,
                                    EVP_CIPHER_CTX *ctx, HMAC_CTX *hctx, int enc)
{
    return 0;
}