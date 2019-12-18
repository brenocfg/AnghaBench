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
typedef  int /*<<< orphan*/  HMAC_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  HMAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_CTX_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_zalloc (int) ; 

HMAC_CTX *HMAC_CTX_new(void)
{
    HMAC_CTX *ctx = OPENSSL_zalloc(sizeof(HMAC_CTX));

    if (ctx != NULL) {
        if (!HMAC_CTX_reset(ctx)) {
            HMAC_CTX_free(ctx);
            return NULL;
        }
    }
    return ctx;
}