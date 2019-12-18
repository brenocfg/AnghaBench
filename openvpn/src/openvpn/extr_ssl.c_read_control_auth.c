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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {scalar_t__ cipher; } ;
struct tls_wrap_ctx {scalar_t__ mode; TYPE_1__ tls_crypt_v2_server_key; int /*<<< orphan*/  opt; } ;
struct tls_options {int dummy; } ;
struct link_socket_actual {int dummy; } ;
struct gc_arena {int dummy; } ;
struct buffer {int /*<<< orphan*/  offset; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__* BPTR (struct buffer*) ; 
 int /*<<< orphan*/  D_TLS_ERRORS ; 
 scalar_t__ const P_CONTROL_HARD_RESET_CLIENT_V3 ; 
 scalar_t__ P_OPCODE_SHIFT ; 
 scalar_t__ SID_SIZE ; 
 scalar_t__ TLS_WRAP_AUTH ; 
 scalar_t__ TLS_WRAP_CRYPT ; 
 scalar_t__ TLS_WRAP_NONE ; 
 struct buffer alloc_buf_gc (int /*<<< orphan*/ ,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_advance (struct buffer*,scalar_t__) ; 
 int /*<<< orphan*/  buf_clear (struct buffer*) ; 
 int /*<<< orphan*/  buf_copy (struct buffer*,struct buffer*) ; 
 int /*<<< orphan*/  buf_forward_capacity_total (struct buffer*) ; 
 int /*<<< orphan*/  buf_init (struct buffer*,int /*<<< orphan*/ ) ; 
 struct buffer clear_buf () ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openvpn_decrypt (struct buffer*,struct buffer,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  print_link_socket_actual (struct link_socket_actual const*,struct gc_arena*) ; 
 int /*<<< orphan*/  swap_hmac (struct buffer*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tls_crypt_unwrap (struct buffer*,struct buffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_crypt_v2_extract_client_key (struct buffer*,struct tls_wrap_ctx*,struct tls_options const*) ; 

__attribute__((used)) static bool
read_control_auth(struct buffer *buf,
                  struct tls_wrap_ctx *ctx,
                  const struct link_socket_actual *from,
                  const struct tls_options *opt)
{
    struct gc_arena gc = gc_new();
    bool ret = false;

    const uint8_t opcode = *(BPTR(buf)) >> P_OPCODE_SHIFT;
    if (opcode == P_CONTROL_HARD_RESET_CLIENT_V3
        && !tls_crypt_v2_extract_client_key(buf, ctx, opt))
    {
        msg(D_TLS_ERRORS,
            "TLS Error: can not extract tls-crypt-v2 client key from %s",
            print_link_socket_actual(from, &gc));
        goto cleanup;
    }

    if (ctx->mode == TLS_WRAP_AUTH)
    {
        struct buffer null = clear_buf();

        /* move the hmac record to the front of the packet */
        if (!swap_hmac(buf, &ctx->opt, true))
        {
            msg(D_TLS_ERRORS,
                "TLS Error: cannot locate HMAC in incoming packet from %s",
                print_link_socket_actual(from, &gc));
            gc_free(&gc);
            return false;
        }

        /* authenticate only (no decrypt) and remove the hmac record
         * from the head of the buffer */
        openvpn_decrypt(buf, null, &ctx->opt, NULL, BPTR(buf));
        if (!buf->len)
        {
            msg(D_TLS_ERRORS,
                "TLS Error: incoming packet authentication failed from %s",
                print_link_socket_actual(from, &gc));
            goto cleanup;
        }

    }
    else if (ctx->mode == TLS_WRAP_CRYPT)
    {
        struct buffer tmp = alloc_buf_gc(buf_forward_capacity_total(buf), &gc);
        if (!tls_crypt_unwrap(buf, &tmp, &ctx->opt))
        {
            msg(D_TLS_ERRORS, "TLS Error: tls-crypt unwrapping failed from %s",
                print_link_socket_actual(from, &gc));
            goto cleanup;
        }
        ASSERT(buf_init(buf, buf->offset));
        ASSERT(buf_copy(buf, &tmp));
        buf_clear(&tmp);
    }
    else if (ctx->tls_crypt_v2_server_key.cipher)
    {
        /* If tls-crypt-v2 is enabled, require *some* wrapping */
        msg(D_TLS_ERRORS, "TLS Error: could not determine wrapping from %s",
            print_link_socket_actual(from, &gc));
        /* TODO Do we want to support using tls-crypt-v2 and no control channel
         * wrapping at all simultaneously?  That would allow server admins to
         * upgrade clients one-by-one without running a second instance, but we
         * should not enable it by default because it breaks DoS-protection.
         * So, add something like --tls-crypt-v2-allow-insecure-fallback ? */
        goto cleanup;
    }

    if (ctx->mode == TLS_WRAP_NONE || ctx->mode == TLS_WRAP_AUTH)
    {
        /* advance buffer pointer past opcode & session_id since our caller
         * already read it */
        buf_advance(buf, SID_SIZE + 1);
    }

    ret = true;
cleanup:
    gc_free(&gc);
    return ret;
}