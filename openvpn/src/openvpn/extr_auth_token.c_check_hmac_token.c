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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  hmac_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int TOKEN_DATA_LEN ; 
 int /*<<< orphan*/  hmac_ctx_final (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hmac_ctx_reset (int /*<<< orphan*/ *) ; 
 int hmac_ctx_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hmac_ctx_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ memcmp_constant_time (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static bool
check_hmac_token(hmac_ctx_t *ctx, const uint8_t *b64decoded, const char *username)
{
    ASSERT(hmac_ctx_size(ctx) == 256/8);

    uint8_t hmac_output[256/8];

    hmac_ctx_reset(ctx);
    hmac_ctx_update(ctx, (uint8_t *) username, (int)strlen(username));
    hmac_ctx_update(ctx, b64decoded, TOKEN_DATA_LEN - 256/8);
    hmac_ctx_final(ctx, hmac_output);

    const uint8_t *hmac = b64decoded + TOKEN_DATA_LEN - 256/8;
    return memcmp_constant_time(&hmac_output, hmac, 32) == 0;
}