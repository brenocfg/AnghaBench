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
struct TYPE_4__ {int /*<<< orphan*/  keys; } ;
struct TYPE_3__ {int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; } ;
struct test_tls_crypt_v2_context {TYPE_2__ client_key2; TYPE_1__ server_keys; int /*<<< orphan*/  gc; int /*<<< orphan*/  metadata; } ;
struct key2 {int /*<<< orphan*/  keys; int /*<<< orphan*/  member_0; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLS_CRYPT_V2_MAX_METADATA_LEN ; 
 int /*<<< orphan*/  TLS_CRYPT_V2_MAX_WKC_LEN ; 
 struct buffer alloc_buf_gc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert_true (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int tls_crypt_v2_unwrap_client_key (struct key2*,struct buffer*,struct buffer,int /*<<< orphan*/ *) ; 
 int tls_crypt_v2_wrap_client_key (struct buffer*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tls_crypt_v2_wrap_unwrap_no_metadata(void **state) {
    struct test_tls_crypt_v2_context *ctx =
            (struct test_tls_crypt_v2_context *) *state;

    struct buffer wrapped_client_key = alloc_buf_gc(TLS_CRYPT_V2_MAX_WKC_LEN,
                                                    &ctx->gc);
    assert_true(tls_crypt_v2_wrap_client_key(&wrapped_client_key,
                                             &ctx->client_key2,
                                             &ctx->metadata,
                                             &ctx->server_keys.encrypt,
                                             &ctx->gc));

    struct buffer unwrap_metadata = alloc_buf_gc(TLS_CRYPT_V2_MAX_METADATA_LEN,
                                                 &ctx->gc);
    struct key2 unwrapped_client_key2 = { 0 };
    assert_true(tls_crypt_v2_unwrap_client_key(&unwrapped_client_key2,
                                               &unwrap_metadata,
                                               wrapped_client_key,
                                               &ctx->server_keys.decrypt));

    assert_true(0 == memcmp(ctx->client_key2.keys, unwrapped_client_key2.keys,
                            sizeof(ctx->client_key2.keys)));
}