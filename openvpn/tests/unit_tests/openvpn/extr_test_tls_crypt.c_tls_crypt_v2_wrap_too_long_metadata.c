#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  encrypt; } ;
struct test_tls_crypt_v2_context {int /*<<< orphan*/  gc; TYPE_1__ server_keys; int /*<<< orphan*/  metadata; int /*<<< orphan*/  client_key2; int /*<<< orphan*/  wkc; } ;

/* Variables and functions */
 scalar_t__ TLS_CRYPT_V2_MAX_METADATA_LEN ; 
 int /*<<< orphan*/  assert_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_inc_len (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  tls_crypt_v2_wrap_client_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tls_crypt_v2_wrap_too_long_metadata(void **state) {
    struct test_tls_crypt_v2_context *ctx =
            (struct test_tls_crypt_v2_context *) *state;

    assert_true(buf_inc_len(&ctx->metadata, TLS_CRYPT_V2_MAX_METADATA_LEN+1));
    assert_false(tls_crypt_v2_wrap_client_key(&ctx->wkc, &ctx->client_key2,
                                              &ctx->metadata,
                                              &ctx->server_keys.encrypt,
                                              &ctx->gc));
}