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
typedef  int /*<<< orphan*/  zero ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; } ;
struct test_tls_crypt_v2_context {int /*<<< orphan*/  unwrapped_metadata; TYPE_1__ server_keys; int /*<<< orphan*/  wkc; int /*<<< orphan*/  gc; int /*<<< orphan*/  metadata; int /*<<< orphan*/  client_key2; } ;
struct key2 {int /*<<< orphan*/  member_0; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 scalar_t__ BLEN (int /*<<< orphan*/ *) ; 
 scalar_t__ TLS_CRYPT_V2_MAX_METADATA_LEN ; 
 struct buffer alloc_buf_gc (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_true (int) ; 
 int /*<<< orphan*/ * buf_write_alloc (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ memcmp (struct key2*,struct key2 const*,int) ; 
 int rand_bytes (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  tls_crypt_v2_unwrap_client_key (struct key2*,struct buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tls_crypt_v2_wrap_client_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tls_crypt_v2_wrap_unwrap_dst_too_small(void **state) {
    struct test_tls_crypt_v2_context *ctx =
            (struct test_tls_crypt_v2_context *) *state;

    uint8_t* metadata =
            buf_write_alloc(&ctx->metadata, TLS_CRYPT_V2_MAX_METADATA_LEN);
    assert_true(rand_bytes(metadata, TLS_CRYPT_V2_MAX_METADATA_LEN));
    assert_true(tls_crypt_v2_wrap_client_key(&ctx->wkc, &ctx->client_key2,
                                             &ctx->metadata,
                                             &ctx->server_keys.encrypt,
                                             &ctx->gc));

    struct key2 unwrapped_client_key2 = { 0 };
    struct buffer unwrapped_metadata =
            alloc_buf_gc(TLS_CRYPT_V2_MAX_METADATA_LEN-1, &ctx->gc);
    assert_false(tls_crypt_v2_unwrap_client_key(&unwrapped_client_key2,
                                                &unwrapped_metadata, ctx->wkc,
                                                &ctx->server_keys.decrypt));

    const struct key2 zero = { 0 };
    assert_true(0 == memcmp(&unwrapped_client_key2, &zero, sizeof(zero)));
    assert_true(0 == BLEN(&ctx->unwrapped_metadata));
}